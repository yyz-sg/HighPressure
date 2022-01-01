BUILDSUCCESS=true

DIREXIST=false
OUTPUT_DIR="build"

BUILD_OUTPUT="Release"
BUILD_OUTPUT_DEST="out"
BUILDDIREXIST=false

[ -d "${OUTPUT_DIR}/" ] && DIREXIST=true
[ -d "${BUILD_OUTPUT_DEST}/" ] && BUILDDIREXIST=true

if ${DIREXIST}
then
	echo "Existing dir, delete exist and create new \"${OUTPUT_DIR}\" directory."
	rm -r ${OUTPUT_DIR} || { echo "Cannot delete existing \"${OUTPUT_DIR}\" directory."; BUILDSUCCESS=false; }
else
	echo "Directory \"${OUTPUT_DIR}\" does not exist. Creat directory."
fi

if ${BUILDSUCCESS}
then
	mkdir ${OUTPUT_DIR} || { echo "Cannot create \"${OUTPUT_DIR}\" directory."; BUILDSUCCESS=false; }
fi

if ${BUILDSUCCESS}
then
	cmake -S . -B "./${OUTPUT_DIR}" || { echo "CMake process failed."; BUILDSUCCESS=false; }
	cmake --build "./${OUTPUT_DIR}/" --config Release
fi

if ${BUILDSUCCESS}
then
	cmake --build "./${OUTPUT_DIR}/" --config Release || { echo "Build process failed."; BUILDSUCCESS=false; }
fi

if ${BUILDDIREXIST}
then
	echo "Existing dir, delete exist and create new \"${BUILD_OUTPUT_DEST}\" directory."
	rm -r ${BUILD_OUTPUT_DEST} || { echo "Cannot delete existing \"${BUILD_OUTPUT_DEST}\" directory."; BUILDSUCCESS=false; }
else
	echo "Directory \"${BUILD_OUTPUT_DEST}\" does not exist. Creat directory."
fi

if ${BUILDSUCCESS}
then
	mkdir ${BUILD_OUTPUT_DEST} || { echo "Cannot create \"${BUILD_OUTPUT_DEST}\" directory."; BUILDSUCCESS=false; }
fi

if ${BUILDSUCCESS}
then
	cp -a ./${OUTPUT_DIR}/${BUILD_OUTPUT}/. ./${BUILD_OUTPUT_DEST}/ || { echo "Cannot copy build ouput to ${BUILD_OUTPUT_DEST}."; BUILDSUCCESS=false; }
fi

if ${BUILDSUCCESS}
then
	echo "Build success."
else
	echo "Build failed."
fi

read -n 1 -s -r -p "Press any key to continue..."
