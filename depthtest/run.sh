clang++ -std=c++11 -stdlib=libc++ -lglfw3 -framework CoreVideo -framework OpenGL -framework IOKit -framework Cocoa -framework Carbon main.cpp ../Shader.cpp ../glad.c -o depthtest.out
./depthtest.out