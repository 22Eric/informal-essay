opencv帮助文档：[](https://docs.opencv.org/4.6.0/index.html)

### 1.配置环境

#### 1.1 基本配置

1. windows电脑
2. Visual Studio 2022 社区版
3. opencv 4.6.0

#### 1.2 进阶配置

点击属性管理器。

![](C:\Users\22594\OneDrive\桌面\study_file\blog\opencvC++Pic\2022-09-23.png)

右击Debug|x64下MicrosoftCPp.x64.user，点击属性。

点击VC++目录。选中包含目录，添加opencv目录下的build/include文件夹，和build/include/opecv2文件夹。

​							选中库目录，添加bulid/x64/vc14/lib文件夹

点击连接器目录下的“输入”。添加“附加依赖项”。opencv版本4.6.0就写opencv_world460d.lib

![](C:\Users\22594\OneDrive\桌面\study_file\blog\opencvC++Pic\2022-09-23 -2.png)

配置环境变量：build文件夹。build/x64/vc14/bin文件夹。build/x64/vc14/lib文件夹

### 2. 读取、修改、写入图片

#### 2.1 接口

与python的opencv相同。`imshow`，`imwrite`，`cvtColor`，`nameWindow`。

#### 2.2 代码

```c++
int main(int argc, int** argv)
{
	Mat mrc = imread("C:\\pic\\1.jpg");
	Mat result;
	if (mrc.empty())
	{
		return -1;
	}
	cvtColor(mrc, result, CV_RGB2BGRA);
	namedWindow("test", CV_WINDOW_NORMAL);
	imshow("test", result);
	imwrite("C:\\pic\\1_2.jpg", result);
	waitKey(0);
	return 0;
}
```

### 3. 矩阵的掩模操作

#### 3.1 接口

`filter2D`

#### 3.2 代码

```c++
//方法一：用接口函数实现（推荐）
int main(int argc, int** argv)
{
	Mat mrc = imread("C:\\pic\\1.jpg");
	Mat result;
	if (mrc.empty())
	{
		return -1;
	}
	namedWindow("test1", CV_WINDOW_NORMAL);
	namedWindow("test2", CV_WINDOW_NORMAL);

	Mat kenal = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(mrc, result, -1, kenal);
	imshow("test1", mrc);
	imshow("test2", result);
	waitKey(0);
	return 0;
}

//方法2：自行实现（用于学习对单个像素的控制，实际使用不推荐）
int main(int argc, int** argv)
{
	Mat mrc    = imread("C:\\pic\\1.jpg");
	Mat result = Mat::zeros(mrc.size(),mrc.type());
	if (mrc.empty())
	{
		return -1;
	}
	namedWindow("test1", CV_WINDOW_NORMAL);
	namedWindow("test2", CV_WINDOW_NORMAL);

	int cols    = (mrc.cols - 1) * mrc.channels();
	int rows    = mrc.rows;
	int offsetx = mrc.channels();

	for (int row = 1; row < rows - 1; row++)
	{
		const uchar *previous = mrc.ptr<uchar>(row - 1);
		const uchar *current  = mrc.ptr<uchar>(row);
		const uchar *next     = mrc.ptr<uchar>(row + 1);
		uchar* output = result.ptr<uchar>(row);
		for (int col = offsetx; col < cols; col++)
		{
			output[col] = saturate_cast<uchar>(5 * current[col] - (current[col - offsetx] + current[col + offsetx] + previous[col] + next[col]));
		}
	}
	imshow("test1", mrc);
	imshow("test2", result);
	waitKey(0);
	return 0;
}
```

### 4.Mat对象

#### 4.1 接口

`void 	copyTo (Mat &dst) const`，`Mat 	clone () const`，`const uchar * 	ptr (int row, int col=0) const`等

#### 4.2 代码

```c++
Mat result = Mat(src.size(), src.type());

Mat result = src.clone();

Mat result;
src.copyTo(result);
```

### 5. 图像操作

#### 5.1 接口

```c++
bool 	cv::imwrite (const String &filename, InputArray img, const std::vector< int > &params=std::vector< int >())

Mat 	cv::imread (const String &filename, int flags=IMREAD_COLOR)

//读写一个gray像素点的值
Scalar intensity = img.at<uchar>(y,x);


//读一个RGB像素点的值
Vec3f intensity = img.at<Vec3f>(y,x);
float blue  = intensity.val[0];
float green = intensity.val[1];
float red   = intensity.val[2];
```

#### 5.2 代码

```c++
int main(int argc, int** argv)
{
	Mat src    = imread("C:\\pic\\1.jpg");
	Mat result = src.clone();

	//cvtColor(src, result, CV_BGR2GRAY);
	int cols = result.cols;
	int rows = result.rows;
	int nc   = result.channels();
	namedWindow("test1", CV_WINDOW_NORMAL);
	namedWindow("test2", CV_WINDOW_NORMAL);
	imshow("test1", result);
	for(int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			if (nc == 3)
			{
				result.at<Vec3b>(i, j)[2] = 0;
			}
		}

    //也可以用
    //bitwise_not
	imshow("test2", result);
	waitKey(0);

	return 0;
}
```

### 6.图像混合

#### 6.1 接口

`addWeighted`,`add`,`multiply`

#### 6.2 代码

```
int main(int argc, int** argv)
{
	Mat src    = imread("C:\\pic\\1.jpg");
	Mat result = imread("C:\\pic\\1_2.jpg");
	Mat dst;
	//bitwise_not(src, result);
	//cvtColor(src, result, CV_BGR2GRAY);
	int cols = result.cols;
	int rows = result.rows;
	int nc   = result.channels();
	namedWindow("test1", CV_WINDOW_NORMAL);
	namedWindow("test2", CV_WINDOW_NORMAL);
	imshow("test1", result);
	addWeighted(src, 0.5, result, 0.5,0.0,dst);

	imshow("test1", result);
	imshow("test2", dst);
	waitKey(0);

	return 0;
}
```

### 7.调整图像亮度与对比度

把图像的r、g、b分别视为一个函数，将其分别乘以alpha再加上beta。其中alpha就是对比度，beta就是亮度。

#### 7.1代码

```c++
int main(int argc, int** argv)
{
	Mat src    = imread("C:\\pic\\1.jpg");
	Mat result;
	Mat dst;

	src.convertTo(result, CV_32F,1.0/255);
	int cols = result.cols;
	int rows = result.rows;
	int nc   = result.channels();
	cout << nc << endl;
	double alpha = 1.2;
	double beta = -0.2;
	namedWindow("test1", CV_WINDOW_NORMAL);
	namedWindow("test2", CV_WINDOW_NORMAL);
	imshow("test1", result);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			result.at<Vec3f>(i, j)[0] =   result.at<Vec3f>(i, j)[0] * alpha + beta;
			result.at<Vec3f>(i, j)[1] = result.at<Vec3f>(i, j)[1] * alpha + beta;
			result.at<Vec3f>(i, j)[2] = result.at<Vec3f>(i, j)[2] * alpha + beta;
		}
	}

	imshow("test2", result);
	//imshow("test2", dst);
	waitKey(0);

	return 0;
}
```

### 8.绘制形状与文字

#### 8.1 接口

`line`，`rectangle`，`circle`，`ellipse//椭圆`，`fillpoly//填充`

#### 8.2 代码

```c++
Mat src;
Mat result;
void f()
{
	Rect rect(100, 100, 500, 500);
	Scalar color = Scalar(0, 0, 0);
	//line(src, a, b, color, 6, LINE_8);
	rectangle(src, rect, Scalar(0, 0, 0));
}
int main(int argc, int** argv)
{
	src    = imread("C:\\pic\\1.jpg");
	cvtColor(src,result,CV_RGB2BGR);
	Mat dst;

	f();

	namedWindow("test2", CV_WINDOW_NORMAL);
	namedWindow("test1", CV_WINDOW_NORMAL);
	imshow("test1", src);

	//imshow("test2", result);

	waitKey(0);

	return 0;
}
```

### 9.图像滤波

#### 9.1 接口

```c++
//均值滤波 Blur
//高斯滤波 GaussianBlur
//中值滤波（适用于椒盐噪声） medianBlur
//双边滤波 bilateralFilter
```

#### 9.2 代码

```c++
int main(int argc, int** argv)
{
	src    = imread("C:\\pic\\1.jpg");
	Mat dst;
	namedWindow("test2", CV_WINDOW_NORMAL);
	namedWindow("test1", CV_WINDOW_NORMAL);

	//Size ksize = Size(21, 21);
	//Blur(src, result, ksize);
	//GaussianBlur(src, result, ksize,11);

	bilateralFilter(src, result, 15, 100, 10);

	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(result, dst, -1, kernel);

	imshow("test1", src);

	imshow("test2", result);

	waitKey(0);

	return 0;
}
```











