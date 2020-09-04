## What's this

[Robomaster](https://www.robomaster.com/zh-CN) Competition 2019. The demostration of classifier from SuperPower Team(from Tongji University, China).

**Note that we just published our demo code to show the main idea of our algorithm. We actually made a better version of code which has higher accuracy and faster interface time** (98+%, 2~3 ms time cost when dealing with 100 pieces of images on our NUC).

Our team was the first team to beat the small energy organ at RM19, and the classifier algorithm used is just what the code of this repo describes.

## Unzip Data And Check File Num

```shell
unzip data

echo "Number of Test Negitive Sample: "
ls -l data/negative | grep '^-' | wc -l
echo "Number of Test Positive Sample: "
ls -l data/positive | grep '^-' | wc -l
```

You'll see:

```
Number of Test Negitive Sample: 
    1493
Number of Test Positive Sample: 
    1470
```

## Run Test

```shell
cd build
cmake .. && make -j4 && ./SP19CLASSIFIER_TEST
```

You'll see:

```
@@@ ../armor/positive ~ 11 file reading finished.
@@@ ../armor/negative ~ 20 file reading finished.
Average bench time: 0.0528991 ms
goods right: 1410 / 1470 ~ 95.9184 %
bads  right: 1469 / 1493 ~ 98.3925 %
Total accuracy: 97.165 %
```

> I ran this code on my MacBook Pro 2015 with clang 8.0. The performance of my Mac is just similar to NUC(And we can get nearly same result on NUC).

## How To Use

#### Prepare Ur Templates

```shell
mkdir template    # The folder to hold positive and negative templates.
cd template				# You can replace "template" with any other name.
mkdir positive    # !!! You cannot replace "positive" with any other name.
mkdir negative    # !!! You cannot replace "negative" with any other name.
# The put positive samples into "positive" folder. "negative" is just as the same.
```

#### API

```c++
#include "classifier.hpp"

int main()
{
  	sp::classifier classifier("../template");
  	auto img = cv::imread(...);
  	
  	// Binary prediction.
  	bool out = classifier.boolean_forward(img);
  	// Get the index of image that "img" matches. 
    // (Only available for positive templates)
  	int index = classifier.forward(img);
}
```

## How To Optimize This

#### Accuracy

- Tune the parameters:
  - Compare strategy
  - Thresholding strategy
  - Use better templates

> Acctually, from my experience, about 5 positive templates and 10 for negative templates can already get a satisfactory result(And, of course, faster).

#### Speed

Use some optimization techniques( this is great ).

Some simple tips that I can share with U:

- SIMD(We enabled "auto-SIMD" via "-march=native" and "-Ofast"), U can include `<intrin.h>` to optimize ur code using other good instructions.
- Always use clang as ur compiler. (Clang is perfect at numeric code optimization, while gcc …)
- Muti-threading. (In our deployment code, I used thread pool technique which can help when dealing with a big image sequence. But of course, pay attention to the strategy of switching single threading and multi-threading)

> Of course, the algorithm it self is simple and effective. No need to optimize too much.
>
> (The fastest answer may be Cuda … )

