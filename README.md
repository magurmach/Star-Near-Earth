#Star Near Earth: A project for finding our neighbors in this Universe

Sun is the star of our solar system. This project is a mere effort for 2-D visualization of the location of neighboring Stars of our solar system. The nearest 9 of them has been marker from 1-9.

##General Description
Starting with a database of 100 stars nearest to SUN ( `nearest_stars.txt` ) the main inspiration of this project was to visualize, how on 2-D projection our neighboring stars look. 2-D projections don't ensure a real view of how they far they are really, but they provide a general idea of the distance. We have completed X-Y, X-Z and X-Y projections against this real data we have collected from [**RECONS**](http://www.chara.gsu.edu/RECONS/) provided [*here*](http://www.chara.gsu.edu/RECONS/TOP100.posted.htm).

##General Class description
###class `StarNearEarth`
This class has simple functionality of storing every information found in the [*data*](http://www.chara.gsu.edu/RECONS/TOP100.posted.htm) file.<br>
1. **`rAsc`***(abbr. RA)*- the ***right ascension***, the east-west position measured from a particular position, the ***Prime Meridian***, on March 21, midnight. It's analogous to the *longitude* here on Earth, but it uses celestial coordinates. Values are in hours from 0 to 24. In my class, I convert this value to a degree in the range of *0-360*.<br>
2. **`decl`***(abbr. DEC)*- the ***declination***, the position of the star north or south of the ***celestial equator***, and is analogous to latitude here on Earth. Values are in degrees from *+90 to -90*.<br>
3. **`parallaxMean`***(abbr. parallax)*- the amount this star seems to move against the background sky (in tiny fractions of a degree called an "arc second".). This is needed to compute the distance in light-years which we want, but which is not part of the data, explicitly.

####Turning RA, DEC and parallex into (x,y,z)
Projecting stars into 2-D from (x-y),(x-z) and (y-z) perspective, we will need (x,y,z). This is why our next class is for.
###class `SNE_Analyzer`
`SNE_Analyzer` class inherits class `StarNearEarth` and contains the function `calcCartCoords()` which calculates the coordinates

###template class **`FHsparseMat.h`**
A linked list implementation of sparse matrix.  Provided methods are:<br>

1. `set(int _row, int _column, const template<class Object\> &)` : sets an object at location (row,column) <br>
2. `template <class Object> get(int _row, int _column)`: get element of (row,column) from matrix<br>
3. `defaultValue`: value returned when the requested location is empty.<br> 
4. `clear()` : Clears the object. <br>
5. `showSubSquare(int _start, int _size)`: Output the sub-matrix between (_start,_start) to (_start+_size,_start+_size)<br>
6. `show()`: show the full matrix

##Output

The programs takes as input `nearest_stars.txt` by default and outputs a list of names of all the stars in the file. Then the program outputs `X-Y` then `X-Z` and then `Y-Z` projection of the data. The nearest 9 stars have been numbered from 1-9 and due to coordinate compression, some stars may not be recognized as different stars in 2-D.