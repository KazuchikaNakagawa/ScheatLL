cmake_minimum_required(VERSION 3.7)
project(Scheatll CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

# libScheatll
add_library(Scheatll STATIC
./API/ScheatLL.cpp
./Attribute/ScLLAttribute.cpp
./Codes/Codes.cpp
./Exec/ScheatLLExec.cpp
./Global/Globals.cpp
./InsertPoint/InsertPoint.cpp
./LLVMConverter/LLVMConverter.cpp
./Nodes/src/BasicNodes.cpp
./Nodes/src/GlobalAllocExpr.cpp
./Nodes/src/DeclareFuncExpr.cpp
./Nodes/src/LocalAllocExpr.cpp
./Nodes/src/ArgumentExpr.cpp
./Nodes/src/ConstantExpr.cpp
./Nodes/src/AssignExpr.cpp
./Nodes/src/ReadExpr.cpp
./Nodes/src/ReferenceExpr.cpp
./Nodes/src/ReturnExpr.cpp
./Nodes/src/IfExprs.cpp
./Type/ScheatLLPointerType.cpp
./Type/ScheatLLType.cpp
./Type/ScLLType.cpp
./Type/ScheatFuncType.cpp
./SourceLocation/SourceLocation.cpp
)

link_directories(/usr/local/opt/llvm/lib)
target_link_libraries(Scheatll PUBLIC LLVM)
include_directories(/usr/local/opt/llvm/include)

add_executable(test
./Test/main.cpp
)

link_directories(/usr/local/opt/llvm/lib)
include_directories(/usr/local/opt/llvm/include)

target_link_libraries(test Scheatll LLVM)
