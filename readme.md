# C++ based image Resizer Web Server using OpenCV

## Build Docker
```
docker build -t image-resizer .
```
## Run Docker
```
docker run -ti --rm --name image-resizer image-resizer-server
```

## hitting the API
Input Payload:
```
Content-Type: application/json
{
    "input_jpeg": "[base 64 encoding of jpeg binary]",
    "desired_width": [target_width],
    "desired_height": [target_height]
}
```
Output Payload:
If success:
```
HTTP 200
Content-Type: application/json
{
    "code": 200,
    "message": "success",
    "output_jpeg": "[base 64 encoding of output jpeg binary]"
}
```
If failed:
```
HTTP 404
Content-Type: application/json
{
    "code": 404,
    "Message": "failed to convert input_image, check your image string!"
}
```