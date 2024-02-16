1.创建窗口

api: `namedWindow`，`imshow`，`waitKey`,`destroyAllWindows`，`resizeWindow`，`imwrite`

2.视频采集

api:`VideoCapure`，`read`，`release`

摄像头：VideoCapure的参数是设备id，可以是0，意味着自动匹配

视频文件：VideoCapure的参数是文件的地址

```python
#ret，frame两个返回值，第一个是布尔值，当read到帧时返回true，第二个参数就是返回的视频帧
ret, frame = cap.read();
```

3.视频存储

api:`VideoWrite`，参数一为输出文件，参数二为多媒体文件格式，参数三为帧率，参数四为分辨率大小

第二个参数用cv2.VideoWriter_fourcc(*"MJPG")格式

默认opencv使用的是640，480采样，如果想用其他采样，可以使用

```python
cap.set(cv2.CAP_PROP_FRAME_WIDTH,1280);
cap.set(cv2.CAP_PROP_FRAME_HEIGHT,720);
```

4.鼠标控制

api：`setMouseCallback(winname,callback)`，`callback(event,x,y,flags,userdata)`

其中，callback是自定义的回调函数

5.opencv的色彩空间

api：`createTrackbar`，`getTrackbarPos`

api: `cvt_img = cv2.cvtColor(img, colorspace[index])  ` ,` cv2.imshow('color', cvt_img)`

6.实现鼠标绘制基本图形

```python
import cv2
import numpy as np



startpos = 0
curshape = 0


img = np.zeros((480,640,3),np.uint8)


def callBack(event,x,y,flags,userdata):
    global startpos,curshape
    if(event & cv2.EVENT_LBUTTONDOWN == cv2.EVENT_LBUTTONDOWN):
        startpos = (x,y)
    elif(event & cv2.EVENT_LBUTTONUP == cv2.EVENT_LBUTTONUP):
        if(curshape == 0):
            cv2.line(img,startpos,(x,y),(255,0,0))
        elif(curshape == 1):
            cv2.rectangle(img,startpos,(x,y),(255,0,0))
        elif(curshape == 2):
            a = x - startpos[0]
            b = y - startpos[1]
            r = int((a**2+b**2)**0.5)
            cv2.circle(img,startpos,r,(255,0,0))
        else:
            print("error")



cv2.namedWindow("drawshape",cv2.WINDOW_NORMAL)


cv2.setMouseCallback("drawshape",callBack)


while True:
    cv2.imshow("drawshape",img)
    key = cv2.waitKey(1) & 0XFF 
    if(key == ord('q')):
        break
    elif(key == ord('l')):
        curshape = 0
    elif(key == ord('r')):
        curshape = 1
    elif(key == ord('c')):
        curshape = 2

cv2.destroyAllWindows()
```

7.给图片添加水印

```python
from os import TMP_MAX
from unittest import result
import cv2
import numpy as np





img = cv2.imread("C:\\pic\\1.jpg")



logo = np.zeros((200,200,3),np.uint8)
mask = np.zeros((200,200),np.uint8)


logo[20:120,20:120] = [0,0,255]
logo[80:180,80:180] = [0,255,0]

mask[20:120,20:120] = 255
mask[80:180,80:180] = 255


m = cv2.bitwise_not(mask)

roi = img[0:200,0:200]



tmp = cv2.bitwise_and(roi, roi, mask = m)

tmp2 = cv2.add(tmp,logo)

img[0:200,0:200] = tmp2



cv2.imwrite("C:\\pic\\3.jpg",img)





cv2.waitKey(0)
cv2.destroyAllWindows()

```

