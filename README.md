# Base source
Base source to re-use in multiple project(C sources)
## Folder structure
```text
abstract
   |-- CMakeLists.txt
   |-- include
   |   |-- abstract_config.h
   |   |-- abstract_enum.h
   |   |-- abstract_errors.h
   |   |-- abstract_event.h
   |   |-- abstract_fd_mon.h
   |   |-- abstract_string_helper.h
   |-- src
   |   |-- abstract_event.c
   |   |-- abstract_fd_mon.c
   |   |-- abstract_string_helper.c
   |-- test
   |   |-- CMakeLists.txt
   |   |-- test_pollfd_mon.c
data_structure
   |-- CMakeLists.txt
   |-- include
   |   |-- linked_list.h
   |-- test
   |   |-- CMakeLists.txt
   |   |-- test_list.c
fdmon_impl
   |-- CMakeLists.txt
   |-- include
   |   |-- mon_factory.h
   |-- internal
   |   |-- epollfd_mon.h
   |   |-- pollfd_mon.h
   |   |-- selectfd_mon.h
   |-- src
   |   |-- epollfd_mon.c
   |   |-- mon_factory.c
   |   |-- pollfd_mon.c
   |   |-- selectfd_mon.c
logger
   |-- CMakeLists.txt
   |-- include
   |   |-- blogger.h
   |-- src
   |   |-- blogger.c
   |-- test
   |   |-- logger_test.c
script
   |-- run_unit_testapp.sh
signal_handler
   |-- CMakeLists.txt
   |-- include
   |   |-- signal_handler.h
   |-- src
   |   |-- signal_handler.c
   |-- test
   |   |-- CMakeLists.txt
   |   |-- signal_test.c
```
- **abstract** is the abstration of the base source, only the abstract info should be store here
- **data_structure** data structure to be use project wide
- **logger** logger for project wide
- **signal_handler** signal handle and backtrace
- **fdmon_impl** concrete implement for fd monitor on linux
- **third_party** third party sources
## How to build
```bash
mkdir build
cd build && cmake ..
make
```