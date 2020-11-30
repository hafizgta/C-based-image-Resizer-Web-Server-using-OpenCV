
<span style="color:red">Please READ: </span>
> This Repo was created as a requirement of a job application. the fact that I was failed to spot on the minor bugs when
> the deadline is due, this page is not showing the working sample of this project, simply checkout the branch finalization to get to the
> working product.
> 
> that branch would be merged to this main branch a week after this
> application process take effect (6/12/2020)

# C++ based openCV image resizer Web Server
this project demonstrate the example of how to make a C++ based image resizer web server.

## Build Docker
```
docker build -t image-resizer .
```
## Run Docker
```
docker run -ti --rm --name image-resizer-server image-resizer 
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
