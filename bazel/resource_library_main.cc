// Copyright (C) 2023 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this
// file except in compliance with the License. You may obtain a copy of the
// License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations under
// the License.

#include <cstdio>
#include <fstream>
#include <vector>

void GenerateComments(std::ostream &f) {
  f << "// This file was automatically generated by resource_library\n";
}

void GenerateExternCOpen(std::ofstream &f) {
  f << "#if __cplusplus\n";
  f << "extern \"C\" {\n";
  f << "#endif // __cplusplus\n\n";
}

void GenerateExternCClose(std::ofstream &f) {
  f << "#if __cplusplus\n";
  f << "}\n";
  f << "#endif // __cplusplus\n\n";
}

std::string MakeVariable(const std::string &s) {
  std::string variable = "RESOURCE_" + s;
  for (char &c : variable) {
    if (c == '-' || c == '.' || c == '/') {
      c = '_';
    }
  }
  return variable;
}

void GenerateResourceEntry(std::ostream &f) {
  f << "struct ResourceEntry {\n";
  f << "  const char* name;             // the file's original name\n";
  f << "  const char* data;             // beginning of the file\n";
  f << "  unsigned int size;            // length of the file\n";
  f << "};\n\n";
}

bool GenerateHeader(const std::string &output_hdr,
                    const std::vector<std::string> &input_files) {
  std::ofstream hdr(output_hdr);
  GenerateComments(hdr);

  hdr << "#pragma once\n\n";
  GenerateExternCOpen(hdr);

  GenerateResourceEntry(hdr);
  // TODO(kangjinci): generate resource entry table

  for (const auto &file : input_files) {
    auto variable = MakeVariable(file);
    std::ifstream f(file, std::ios::binary | std::ios::ate);
    if (!f.is_open()) {
      printf("open file %s failed\n", file.c_str());
      return false;
    }
    hdr << "// " << file << "\n";
    hdr << "extern const char " << variable << "[" << f.tellg() << "];\n";
    hdr << "extern const unsigned " << variable << "_len;\n\n";
    f.close();
  }

  GenerateExternCClose(hdr);

  return true;
}

bool GenerateSource(const std::string &output_src,
                    const std::vector<std::string> &input_files,
                    const std::vector<std::string> &output_files) {
  std::ofstream src(output_src);
  GenerateComments(src);
  // TODO(kangjinci): generate resource entry table

  size_t size = input_files.size();
  for (size_t i = 0; i < size; ++i) {
    std::ifstream input(input_files[i], std::ios::binary | std::ios::ate);
    std::ofstream output(output_files[i]);

    if (!input.is_open()) {
      printf("open file %s failed\n", input_files[i].c_str());
      return false;
    }

    auto file_size = input.tellg();
    input.seekg(0);

    GenerateComments(output);

    auto variable = MakeVariable(input_files[i]);
    output << "const char " << variable << "[] = {\n";

    char buf[13] = {0};
    do {
      output << " ";
      input.read(buf, 12);
      for (short c : buf) {
        if (c == '\0') {
          break;
        }
        output << c << ", ";
      }
      output << "\n";
    } while (!input.eof());

    output << "};\n";
    output << "const unsigned int " << variable << "_len = " << file_size
           << ";\n\n";

    input.close();
    output.close();
  }

  return true;
}

int main(int argc, char **argv) {
  if (argc == 1) {
    printf("Please specify the output header and source files\n");
    return -1;
  }

  if (argc < 4) {
    printf("Please specify the input source files\n");
    return -1;
  }

  if ((argc - 3) % 2 == 1) {
    printf("Invalid arguments\n");
    return -1;
  }
  int size = (argc - 3) / 2;

  std::vector<std::string> output_files(argv + 3, argv + 3 + size);
  std::vector<std::string> input_files(argv + 3 + size, argv + argc);

  if (!GenerateHeader(argv[1], input_files)) {
    return -1;
  }

  if (!GenerateSource(argv[2], input_files, output_files)) {
    return -1;
  }
}