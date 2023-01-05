MAP_DIR=./miro_tests


for i in {1..10}
do
	printf "$MAP_DIR/map_$i" | rev | cut -d '/' -f 1 | rev >> test_results
	head -n 2 "$MAP_DIR/map_$i"  | grep "required" | cut -d : -f2 >> test_results
	../lem-in -qt < "$MAP_DIR/map_$i" >> test_results
	printf "\n\n___________________________________________________\n" >> test_results
done
