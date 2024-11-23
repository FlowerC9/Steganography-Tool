# Steganography Tool

- Video Demo

1. ## Introduction

- This is a command-line steganography tool written in C++ that allows you to hide and extract secret messages within PNG images using the Least Significant Bit (LSB) technique. The tool utilizes the LodePNG library for image processing, making it cross-platform and easy to use without external dependencies.

2. ## Features

    - Embed Messages: Hide secret text messages inside PNG images.
    - Extract Messages: Retrieve hidden messages from stego-PNG images.
    - Cross-Platform: Works on Windows, Linux, and macOS.
    - No External Dependencies: Uses LodePNG, a single-header PNG library.
    - Simple Command-Line Interface: Easy to use with straightforward commands.

3. ## Requirements
    - C++ Compiler: Any standard C++ compiler (e.g., GCC, Clang, MSVC).
    - LodePNG Library: Included in the project files (lodepng.h and lodepng.cpp).

4. ## Installation
- open terminal and type following commands
    ```
    git clone https://github.com/YourUsername/SteganographyTool.git
    ```

    ```
    cd SteganographyTool
    ```
    ```
    g++ -o steganography_tool steganography_tool.cpp lodepng/lodepng.cpp
    ```
    ```
    steganography_tool --embed <input_png> <output_png> <message_file>
    ```
    ```
    steganography_tool --extract <input_png> <output_text_file>
    ```

5. ## Cautions
- ***Message Size Limit***: The maximum size of the message is limited by the image's capacity. Each byte of the image can store one bit of the message.
- ***Image Quality***: The embedding process makes minimal changes to the image, generally imperceptible to the human eye.
- ***Binary Mode for Files***: Files are read and written in binary mode to ensure compatibility across different operating systems.
- ***Null Terminator***: A null character ('\0') is used to signify the end of the message during extraction.
- ***Color Channels***: LodePNG decodes images into RGBA format. The image data vector contains 4 bytes per pixel (Red, Green, Blue, Alpha).

6. ## Contact
    - ***Author***:Monojit Tewari
    - ***Email***:[Email](tewarimonojit@gmail.com)
    - ***LinkedIn***:[LinkedIn](https://www.linkedin.com/in/monojit-tewari)