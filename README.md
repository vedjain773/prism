# Prism

A real-time music visualizer built in C, inspired by [cava](https://github.com/karlstav/cava).

![demo_gif](assets/demo.gif)

---

Prism performs real-time FFT analysis on system audio and renders a smooth, logarithmically scaled frequency spectrum with user configurable decays, colors and gradients.

The project uses:
* [miniaudio](https://miniaud.io/docs/manual/index.html)
   - To capture background audio
* [raylib](https://www.raylib.com/)
   - As the GUI library to display the visualiser

For computing Fast Fourier transforms the project makes use of CFFT, a custom FFT static lib 
written in C which suits the need of the project well.
The library is a radix-2 implementation of the Cooley-Tuchey algorithm and performs similar to
KissFFT on most platforms.

## Usage
Clone the repository
```bash
git clone https://github.com/vedjain773/Prism.git && cd Prism
```

Run the installation script to install all the dependencies
```bash
chmod +x install.sh
./install.sh
```

Build the project and run the built executable
```bash
make
./prism
```

## Background
Prism is the spiritual successor to [spectra-view](https://github.com/vedjain773/spectra-view), an earlier, more educational project where I built the entire pipeline from scratch — WAV parsing, DFT calculation, and terminal rendering. It taught me a lot about signal processing, but it was slow (a naive DFT took minutes on even 8–10 second WAV files) and the visuals were jittery and noisy compared to cava.

Prism is a rebuild on proven libraries instead of from-scratch code. I stuck with C because:

* Every library I wanted to use (miniaudio, raylib) is written in C
* The project didn't need C++'s abstractions
* I wanted a break from C++ after a long stretch of it
