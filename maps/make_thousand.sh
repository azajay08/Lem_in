MAP_DIR=./miro_tests

if [ ! -d "$MAP_DIR" ]
then
	mkdir "$MAP_DIR"
fi

for i in {1..10}
do
	"./generator" --flow-thousand > "$MAP_DIR/map_$i"
	sleep 1
done
