

# C++ based openCV image resizer Web Server
this project demonstrate the example of how to make a C++ based image resizer web server.

## Build Docker
```
docker build -t image-resizer .
```
## Run Docker
```
docker run -p 8080 --rm --name image-resizer-server image-resizer 
```

## hitting the API
API address and host:
```
HTTP://[host_address]:8080/resize_image [POST]
```
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
