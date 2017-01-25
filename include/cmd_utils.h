#ifndef DENSEFLOW_CMD_UTILS_H
#define DENSEFLOW_CMD_UTILS_H
#define PRINT_HELP_IF_FLAGGED(parser) \
if (parser.get<bool>("help")) { \
  std::cout << "USAGE: " << argv[0] << " [OPTIONS]" << std::endl; \
  parser.printParams(); \
  return 0; \
}
#endif //DENSEFLOW_CMD_UTILS_H
