# m2g

A 2D graphic library based on SFML2.


## Current status

Active. This project is being developed (branch "experimental") along with the [game JDB](https://github.com/moisesjbc/JDB).


## Building and installing from source (only tested on Ubuntu 14.04)

1. Install [SFML](http://www.sfml-dev.org/download.php) (>= v2.2)

2. Install [TinyXML2](https://github.com/leethomason/tinyxml2)

 ```
 sudo apt-get install libtinyxml2-dev
 ```

3. Clone this repository in local.

 ```
 git clone git@github.com:moisesjbc/m2g.git
 ```

4. Enter in the "build" directory inside the cloned repository.

 ```
 cd m2g/build
 ```

5. Install the library on your system.

```
cmake .
make
sudo make install
```

### Building and runing tests

If you don't trust me, you can build and run m2g's automated tests (unless you 
don't trust my tests neither).

1. Install [Google Mock](https://code.google.com/p/googlemock/)

2. Install [Catch](https://github.com/philsquared/Catch)

 ```
 sudo apt-get install catch
 ```

3. Within the "build" directory, build and run tests

 ```
 cmake -DTESTS=1 .
 make
 cd tests
 ./tests
 ```
