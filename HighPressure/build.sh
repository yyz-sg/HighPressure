DIREXIST=false
BUILDSUCCESS=true
OUTPUT_DIR="build"


[ -d "${OUTPUT_DIR}/" ] && DIREXIST=true

if ${DIREXIST}
then
	echo "Existing dir, delete exist and create new \"${OUTPUT_DIR}\" directory."
	rm -r ${OUTPUT_DIR} || { echo "Cannot delete existing \"${OUTPUT_DIR}\" directory."; BUILDSUCCESS=false; }
else
	echo "Directory \"${OUTPUT_DIR}\" does not exist. Creat directory."
fi


if ${BUILDSUCCESS}
then
	mkdir ${OUTPUT_DIR} || { echo "Can't create \"${OUTPUT_DIR}\" directory."; BUILDSUCCESS=false; }
fi

if ${BUILDSUCCESS}
then
	cmake -S . -B "./${OUTPUT_DIR}" || { echo "CMake process failed."; BUILDSUCCESS=false; }
fi

if ${BUILDSUCCESS}
then
	echo "Build success."
else
	echo "Build failed."
fi

read -n 1 -s -r -p "Press any key to continue..."