# Fast MRMR

This project contains a C++ implementation of the [mRMR algorithm](http://home.penglab.com/proj/mRMR/).


### Boost library

You need [boost](http://www.boost.org/) libraries installed on your computer

If you are running OSX you can install them with [hombrew](https://brew.sh/index.html)

    brew install boost



### Compiling

    make


This generates a binary file called `fast_mrmr` this file will read raw data from the `data.mrmr` file.

You can pass the following parameters:
    -c <index of class feature>		Used to select index of class feature. (from 1 to number of features)
    -f <number of mrmr features required>	 Indicates the how many features to select.



- Read more about **.mrmr format** [here](https://github.com/IagoLast/mrmr-datareader)
- We provide binarized versions of the [example datasets](http://home.penglab.com/proj/mRMR/) in the under the datasets folder.