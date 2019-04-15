# LCview: An offline viewer for LendingClub notes statistics

LendingClub provides some features to display notes statistics on its
website, but the filter and display capabilities are quite limited.

This project aims at building a desktop application that can provide a
richer set of statistics, while still allowing filtering of notes.

For example:

![Example](docs/images/summary-example.png)

## Installation

To use `lcview`, you need to build it from the source
code. Pre-compiled binaries are not provided at this time.

### Install dependencies

You need to install a compiler that supports `c++17`. Development was
performed against `gcc-8.2.0`.

You need the development version of the QT libraries. If you are not
using a monolithic package, you should install at least these
components: `qt-charts`, `qt-core`, `qt-gui`and
`qt-widgets`. Development was performed against QT version `5.11.x`.

*The exact commands to be used depend on your Linux
distribution. Please refer to the documentation of your distribution
for more information.*


### Build from source

```
git clone https://github.com/dark/lcview.git
cd lcview
mkdir build  # all generated files will be in this directory
cd build
qmake ..
make
```

Run `./lcview` to start the application.

## Usage

To display notes statistics, you need to download on your computer a
CSV file with all notes information.

After logging into your LendingClub account, click on "Holding", then
"Notes":

![Step 1](docs/images/usage-step-1.png)


Then proceed at the bottom of the page; under the pagination widget
there is a link "Download All - Extended".

![Step 2](docs/images/usage-step-2.png)


Click on this link to save the CSV file locally. You should load this
file in `lcview` to display statistics.
