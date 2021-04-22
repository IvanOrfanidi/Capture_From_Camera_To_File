#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    // Open the default video camera.
    cv::VideoCapture cap(cv::VideoCaptureAPIs::CAP_ANY);

    // If not success, exit program.
    if (cap.isOpened() == false) {
        std::cerr << "Cannot open the video camera!" << std::endl;
        return EXIT_FAILURE;
    }

    const double width = cap.get(cv::CAP_PROP_FRAME_WIDTH); // Get the width of frames of the video.
    const double height = cap.get(cv::CAP_PROP_FRAME_HEIGHT); // Get the height of frames of the video.
    std::cout << "Resolution of the video: " << width << " x " << height << "." << std::endl;

    const double fps = cap.get(cv::CAP_PROP_FPS);
    std::cout << "Frames per seconds: " << fps << "." << std::endl;

    static constexpr std::string_view window_name = "My Camera";
    cv::namedWindow(window_name.data()); // Create a window called "My Camera".

    // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file.
    static constexpr std::string_view OUTPUT_NAME_FILE = "outcpp.avi";
    cv::VideoWriter video(OUTPUT_NAME_FILE.data(), cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, cv::Size(width, height));

    // Wait for for 10 ms until any key is pressed.
    // If any key is not pressed withing 10 ms, continue the loop.
    static constexpr int ESCAPE_KEY = 27;
    static constexpr int DELAY_MS = 10;
    while (cv::waitKey(DELAY_MS) != ESCAPE_KEY) {
        cv::Mat frame;

        // Read a new frame from video.
        if (cap.read(frame) == false) { // Breaking the while loop if the frames cannot be captured.
            std::cerr << "Video camera is disconnected!" << std::endl;
            return EXIT_FAILURE;
        }

        // Write the frame into the file.
        video.write(frame);

        // Show the frame in the created window.
        imshow(window_name.data(), frame);
    }
    std::cout << "Esc key is pressed by user. Stoppig the video." << std::endl;

    // When everything done, release the video capture and write object.
    cap.release();
    video.release();

    // Closes all the frames.
    cv::destroyAllWindows();

    return EXIT_SUCCESS;
}