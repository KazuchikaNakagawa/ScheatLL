cmake_minimum_required(VERSION 3.7)
project(Scheatll CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -DDEBUG -g")

# libScheatll
add_library(Scheatll STATIC
./ScheatLL/ScheatLL.cpp
./Attribute/ScLLAttribute.cpp
./Codes/Codes.cpp
./Exec/ScheatLLExec.cpp
./Exec/Implements/IndentManagerImpl.cpp
./Exec/Implements/StructManagerImpl.cpp
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
./Nodes/src/WhileExpr.cpp
./Nodes/src/DefaultOperatorsExpr.cpp
./Nodes/src/CallExpr.cpp
./Nodes/src/ParenExpr.cpp
./Nodes/src/ExternalFuncExpr.cpp
./Nodes/src/GetElementExpr.cpp
./Type/ScheatLLPointerType.cpp
./Type/ScheatLLType.cpp
./Type/ScLLType.cpp
./Type/ScheatFuncType.cpp
./Type/OperatorImpl.cpp
./Type/MemberImpl.cpp
./Type/ScheatStruct.cpp
./SourceLocation/SourceLocation.cpp
./String/String.cpp
)

link_directories(/usr/local/opt/llvm/lib)
target_link_libraries(Scheatll PUBLIC LLVM)
include_directories(/usr/local/opt/llvm/include)

add_executable(test
./Test/main.cpp
)

add_executable(
    stdmaker
    ./ScheatStd/main.cpp
)

link_directories(/usr/local/opt/llvm/lib)
include_directories(/usr/local/opt/llvm/include)

target_link_libraries(test Scheatll LLVM)
target_link_libraries(stdmaker Scheatll LLVM)

add_custom_target(link COMMAND 
"ln" "-s" "-f" "libScheatll.a" "/usr/local/lib/libScheatll.a" ";"
"mv" "./scheatstd.o" "/usr/local/lib/scheatstd.o"
)