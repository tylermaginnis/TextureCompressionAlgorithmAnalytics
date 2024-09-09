# Texture Compression Algorithm Analytics

## Overview
This project, `TextureCompressionAlgorithmAnalytics`, is designed to analyze and compare various texture compression algorithms. It includes a shader compiler and utilizes several image formats and compression techniques.

## Project Structure
- **ShaderCompiler**: Contains the shader compiler code and related files.
  - `CMakeLists.txt`: CMake configuration file for building the shader compiler.
  - `include/stb_image.h`: Header file for image loading and processing.

## Building the Project
To build the project, you need to have CMake installed. Follow these steps:

1. **Clone the repository**:
   ```sh
   git clone https://github.com/yourusername/TextureCompressionAlgorithmAnalytics.git
   cd TextureCompressionAlgorithmAnalytics
   ```

2. **Create a build directory**:
   ```sh
   mkdir build
   cd build
   ```

3. **Run CMake**:
   ```sh
   cmake ..
   ```

4. **Build the project**:
   ```sh
   cmake --build .
   ```

5. **Copy executable to the root directory**:

    ```sh
    cp Debug/ShaderCompiler.exe ..
    ```

6. **Return to the root directory**:

    ```sh
    cd ..
    ```

6. **Run the project**:
    ```sh
    ./ShaderCompiler.exe samples/ output/
    ```

## Usage
After building the project, you can run the shader compiler executable:

## CLI Output:

```bash
AzureAD+TylerMaginnis@DESKTOP-QHFRBJ5 MINGW64 /c/dev/ShaderCompiler/TextureCompressionAlgorithmAnalytics
$ ./ShaderCompiler.exe samples/ output/
Compressing using DXT1...
Starting DXT1 compression...
DXT1 compression has a fixed compression ratio of 1:8.
Each 4x4 pixel block is compressed to 64 bits from 512 bits.
This results in quality loss depending on the original texture.
DXT1 compression completed.
Input File: samples/Sample-png-image-100kb.png
Input File Size: 104327 bytes
Image Dimensions: 272x170
Number of Channels: 4
Output File: output//Sample-png-image-100kb.png.0.compressed
Output File Size: 23392 bytes
Compression Ratio: 4.45994
Uncompressing using DXT1...
Starting DXT1 decompression...
DXT1 decompression completed.
Compressing using DXT1...
Starting DXT1 compression...
DXT1 compression has a fixed compression ratio of 1:8.
Each 4x4 pixel block is compressed to 64 bits from 512 bits.
This results in quality loss depending on the original texture.
DXT1 compression completed.
Input File: samples/Sample-png-image-10mb.png
Input File Size: 10473459 bytes
Image Dimensions: 3984x1538
Number of Channels: 4
Output File: output//Sample-png-image-10mb.png.0.compressed
Output File Size: 3067680 bytes
Compression Ratio: 3.41413
Uncompressing using DXT1...
Starting DXT1 decompression...
DXT1 decompression completed.
Compressing using DXT1...
Starting DXT1 compression...
DXT1 compression has a fixed compression ratio of 1:8.
Each 4x4 pixel block is compressed to 64 bits from 512 bits.
This results in quality loss depending on the original texture.
DXT1 compression completed.
Input File: samples/Sample-png-image-1mb.png
Input File Size: 1068158 bytes
Image Dimensions: 912x513
Number of Channels: 4
Output File: output//Sample-png-image-1mb.png.0.compressed
Output File Size: 235296 bytes
Compression Ratio: 4.53964
Uncompressing using DXT1...
Starting DXT1 decompression...
DXT1 decompression completed.
Compressing using DXT1...
Starting DXT1 compression...
DXT1 compression has a fixed compression ratio of 1:8.
Each 4x4 pixel block is compressed to 64 bits from 512 bits.
This results in quality loss depending on the original texture.
DXT1 compression completed.
Input File: samples/Sample-png-image-200kb.png
Input File Size: 207071 bytes
Image Dimensions: 400x250
Number of Channels: 4
Output File: output//Sample-png-image-200kb.png.0.compressed
Output File Size: 50400 bytes
Compression Ratio: 4.10855
Uncompressing using DXT1...
Starting DXT1 decompression...
DXT1 decompression completed.
Compressing using DXT1...
Starting DXT1 compression...
DXT1 compression has a fixed compression ratio of 1:8.
Each 4x4 pixel block is compressed to 64 bits from 512 bits.
This results in quality loss depending on the original texture.
DXT1 compression completed.
Input File: samples/Sample-png-image-20mb.png
Input File Size: 21141605 bytes
Image Dimensions: 5891x2271
Number of Channels: 4
Output File: output//Sample-png-image-20mb.png.0.compressed
Output File Size: 6693312 bytes
Compression Ratio: 3.15862
Uncompressing using DXT1...
Starting DXT1 decompression...
DXT1 decompression completed.
Compressing using DXT1...
Starting DXT1 compression...
DXT1 compression has a fixed compression ratio of 1:8.
Each 4x4 pixel block is compressed to 64 bits from 512 bits.
This results in quality loss depending on the original texture.
DXT1 compression completed.
Input File: samples/Sample-png-image-30mb.png
Input File Size: 32916531 bytes
Image Dimensions: 7345x2832
Number of Channels: 4
Output File: output//Sample-png-image-30mb.png.0.compressed
Output File Size: 10404768 bytes
Compression Ratio: 3.1636
Uncompressing using DXT1...
Starting DXT1 decompression...
DXT1 decompression completed.
Compressing using DXT1...
Starting DXT1 compression...
DXT1 compression has a fixed compression ratio of 1:8.
Each 4x4 pixel block is compressed to 64 bits from 512 bits.
This results in quality loss depending on the original texture.
DXT1 compression completed.
Input File: samples/Sample-png-image-3mb.png
Input File Size: 3124201 bytes
Image Dimensions: 1920x1080
Number of Channels: 4
Output File: output//Sample-png-image-3mb.png.0.compressed
Output File Size: 1036800 bytes
Compression Ratio: 3.01331
Uncompressing using DXT1...
Starting DXT1 decompression...
DXT1 decompression completed.
Compressing using DXT1...
Starting DXT1 compression...
DXT1 compression has a fixed compression ratio of 1:8.
Each 4x4 pixel block is compressed to 64 bits from 512 bits.
This results in quality loss depending on the original texture.
DXT1 compression completed.
Input File: samples/Sample-png-image-500kb.png
Input File Size: 503111 bytes
Image Dimensions: 800x500
Number of Channels: 4
Output File: output//Sample-png-image-500kb.png.0.compressed
Output File Size: 200000 bytes
Compression Ratio: 2.51555
Uncompressing using DXT1...
Starting DXT1 decompression...
DXT1 decompression completed.
Compressing using DXT1...
Starting DXT1 compression...
DXT1 compression has a fixed compression ratio of 1:8.
Each 4x4 pixel block is compressed to 64 bits from 512 bits.
This results in quality loss depending on the original texture.
DXT1 compression completed.
Input File: samples/Sample-png-image-5mb.png
Input File Size: 5249494 bytes
Image Dimensions: 1800x1350
Number of Channels: 4
Output File: output//Sample-png-image-5mb.png.0.compressed
Output File Size: 1216800 bytes
Compression Ratio: 4.31418
Uncompressing using DXT1...
Starting DXT1 decompression...
DXT1 decompression completed.
```

## Dependencies
- **CMake**: Version 3.10 or higher is required to build the project.
- **C++17**: The project is written in C++17, so a compatible compiler is necessary.
- **stb_image**: The project uses the `stb_image` and `stb_image_write` library for loading and writing images. The library is included in the `include` directory and is used to read PNG files in the project.

## Contributors
The project includes contributions from various developers for different image formats and features. For a detailed list of contributors, refer to the `include/stb_image.h` and `include/stb_image_write.h` file.

## License
This project is licensed under the MIT License. See the `LICENSE` file for more details.

## Contact
For any questions or suggestions, please open an issue on the GitHub repository.