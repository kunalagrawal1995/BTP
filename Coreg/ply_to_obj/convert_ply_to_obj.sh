# this file preprocesses the MPI-FAUST training scans to convert them to obj files.

gcc ply_io.c ply_to_obj.c -lm -o p2o
data_dir=/home/kunala/Documents/BTP/MPI-FAUST/training/scans/*.ply
ext=.obj
new_dir=../test_data/training_scans/
for file in $data_dir
do
	echo "processing $file"
	temp_file_name=${file:52}
	length=${#temp_file_name}
	new_file_name=${temp_file_name:0:length-4}

	./p2o < $file > $new_dir$new_file_name$ext
done
