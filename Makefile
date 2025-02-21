all:
	@echo "Configuring..."
	@cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
	@echo "Building..."
	@cmake --build build
clean:
	@echo "Cleaning up..."
	@rm -rf build

