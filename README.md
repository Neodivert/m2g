# m2g

A 2D graphic library based on SFML2.


## Current status

Active. This project is being developed (branch "experimental") along with the [game JDB](https://github.com/moisesjbc/JDB).


## Building and installing from source (only tested on Ubuntu 14.04)

1. Install [SFML](http://www.sfml-dev.org/download.php) (>= v2.2)

2. Install [Google Mock](https://code.google.com/p/googlemock/)

3. Install the rest of dependencies

 ```
 sudo apt-get install libtinyxml2-dev catch
 ```

4. Clone this repository in local.

 ```
 git clone git@github.com:moisesjbc/m2g.git
 ```

5. Enter in the "build" directory inside the cloned repository.

 ```
 cd m2g/build
 ```

6. Install the library on your system.

```
cmake .
make
sudo make install
```
