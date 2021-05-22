## stl_containers
Implement the various container types of the C++ standard template library. At the 98-th standard.
### Namespase : 'ft'
Includes: list, vector, stack, queue, map. </br>
### [Vector](https://en.cppreference.com/w/cpp/container/vector)
Is a sequence container that encapsulates dynamic size arrays. </br>
### [List](https://en.cppreference.com/w/cpp/container/list)
is a container that supports constant time insertion and removal of elements from anywhere in the container. Fast random access is not supported. Ring bidirectional list. Fast sorting algorithm. </br>
### [Map](https://en.cppreference.com/w/cpp/container/map)
Is a sorted associative container that contains key-value pairs with unique keys. Keys are sorted by using the comparison function Compare. Search, removal, and insertion operations have logarithmic complexity. Based on AVL-tree. </br>
### [Stack](https://en.cppreference.com/w/cpp/container/stack)/[Queue](https://en.cppreference.com/w/cpp/container/queue)
List-based. </br>

### Overall </br>
SFINAE realized by myself.
In map_drawer directory placed source files about programm which vizualize ft::map with insertion option. Using: SFML dynamic library (MacOS).

## To launch map vizualization:
	cmake CMakeLists.txt && make && ./map_drawer

 Options: </br>
 	ADD - default option. Put number in standard input, thes will add in ft_map </br>
	DELETE - comming soon. </br>
