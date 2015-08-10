# Sirv module

The Sirv module provides support within Drupal for the image services provided by [Sirv](http://sirv.com/), including dynamic images and Sirv Zoom. Support for Sirv Spin will be added soon.

## Dependencies

This module requires Drupal 7.36 or later.

To use Sirv’s image services within Drupal, you will need either a free or paid Sirv account. For more information or to create an account, visit [sirv.com](http://sirv.com/).

In order to allow images to be uploaded to Sirv within Drupal, a module that provides integration with Amazon’s S3 file service is required. Some options are:

- [S3 File System](https://www.drupal.org/project/s3fs)
- [AmazonS3](https://www.drupal.org/project/amazons3)
- An S3 container within [Storage API](https://www.drupal.org/project/storage_api)

This module has currently only been tested with the S3 File System module, though it should theoretically work with any module that provides integration with S3.

**Important: In order to use Sirv for image fields, you will need to remove the itok query parameter from image URLs by adding the following line to your settings.php file:**

```$conf['image_suppress_itok_output'] = TRUE;```

## What does this module do?

### Dynamic images

Sirv can be used as a replacement for Drupal’s core image styles, which provide options for scaling, cropping, and other methods of manipulation. Besides the core image effects provided by Drupal, Sirv offers many more options, including rotation, color adjustment and filtering, vignette effects, frames, and watermarks.

The equivalent of Drupal’s image styles in Sirv are profiles, which are stored in JSON format in files within your Sirv account. Profiles are packages of options, available for use by any images uploaded to your account.

In order to make Sirv profiles available within Drupal, enter your connection information (key, secret key, bucket, host, and profiles directory) on Sirv’s main configuration page (/admin/config/media/sirv). 

If you are using a module that allows S3 to be used for image fields, choose S3 as your upload destination when creating the field. Then select Sirv Image as the format for the field and enter your settings, which include a Sirv profile to use to process the image, along with additional options to apply to that field.

### Sirv Zoom

Sirv Zoom lets you rapidly zoom into images to see detail. Zoom options can be be combined into profiles within Drupal (/admin/config/media/sirv/zoom-profiles).

To make into a Sirv Zoom any image (or images) uploaded with an image field, select Sirv Zoom as the format for the field and enter your settings, which include a Sirv Zoom profile to use, along with any additional zoom options to apply Sirv profile to apply to that field. You can also select a default Sirv Image profile to use to process the image and additional profiles that can apply at specified breakpoints.

If multiple images are uploaded to the field, they can either be grouped into one Zoom, which enables thumbnails for navigating between images, or each image can be rendered as a separate Zoom.

For best results with Sirv Zoom, upload the highest-resolution version of your image that you have.

### Sirv Spin

Sirv Spin provides support for 360-degree and 3D spinning images. This module does not yet support Sirv Spin.

## Installation

Install and enable the module in the usual Drupal fashion. In order to upload images to Sirv with a standard Drupal file field, you will need to install a module that allows Amazon S3 to be used for file storage. You will also need to add the following line to your settings.php file:

```$conf['image_suppress_itok_output'] = TRUE;```

