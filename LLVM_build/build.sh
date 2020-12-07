cmake -G "Unix Makefiles" -DLLVM_ENABLE_PROJECTS="clang;lldb;compiler-rt;lld;polly;debuginfo-tests" ../LLVM_src/llvm/
make -j4
sudo make install
