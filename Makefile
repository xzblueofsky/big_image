#order
TARGET:=big_image
$(TARGET):./big_image.cpp
	g++ big_image.cpp -lopencv_core -lopencv_imgproc  -lopencv_highgui -o $(TARGET)
