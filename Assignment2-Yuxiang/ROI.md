# Selecting Bounding Box

> using `selectROI`

## Select a region of interest in OpenCV

```cpp
int main() {
    // Read image
    auto im = imread("image.jpg");

    // Select ROI
    auto r = selectROI(im);

    // Crop image
    auto imCrop = im(r);

    // Display Cropped Image
    imshow("Image", imCrop);
    waitKey(0);

    return 0;
}
```
