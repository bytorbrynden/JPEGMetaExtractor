# JPEG Meta Extractor

Welcome to the repository, it's the home of my "JPEG Meta Extractor" project.

## Introduction

This is an extractor that, when given a JPEG file, will *attempt* to find, and extract metadata (Exif attributes) from the file.

If you want to learn more about Exif, I'd highly recommend that you check out some of the [resources that I used](#resources).

## Details, details

The above section is a valid introduction, but it doesn't explain why I started this project, or what it took for me to create this.

As part of another project that I'm working on (which I'm not at liberty to go into detail about), I needed to be able to fetch GPS data from a JPEG file...

### Easy, *right*?

In theory, what I just described, should be a simple task, as there are lots of tools/libraries that are designed to do just that.

The reason that this turned out to be a less-than-easy task, is because I'm stubborn. Stubborn as in I didn't want to use any libraries, nor did I want to fork any existing code.

### I wanted to write this entirely from scratch.

When I started this project, I made 2 assumptions:

 1. This will be a simple task.
 2. I'll have something working within a day or two.

So, let's see, 2 assumptions. Which were correct assumptions for me to make?

 1. This was a simple task...**once I figured everything out**.
 2. I had something working within a day...**after 3+ days of writing code, and deleting even more code**.

So, I **wanted** to write this entirely from scratch, and guess what?

### I *did* write this entirely from scratch.

After many hours of reading (like, *a lot* of many hours), a light-bulb went off in my head. I was confident that I finally understood the basics of the concept of Exif.

Sometime in the middle-part of the morning on June 7th, 2016, I compiled my code, ran it, and, much to my surprise, it worked. It did exactly what I wanted it to do.

That's when I decided I was ready to rewrite the history of this repository (thus deleting all evidence that this simple program took me quite a while to write), and make it public.

## Resources

I started this project, knowing hardly anything about Exif. Now, I feel I have a really good understanding of Exif.

I used the following resources to help me get a firm understanding of Exif, and I'd definitely recommend that you check them out.

 - [Exif version 2.2 Specification](http://www.exif.org/Exif2-2.PDF)
 - [Anatomy of a JPG image](http://itbrigadeinc.com/post/2012/03/06/Anatomy-of-a-JPG-image.aspx)
 - [Location data within JPGs](http://forensicsfromthesausagefactory.blogspot.com/2013/03/location-data-within-jpgs.html)
 - [Exif file format](http://www.media.mit.edu/pia/Research/deepview/exif.html)
 - [JPEG header format](http://www.fastgraph.com/help/jpeg_header_format.html)
 - [Exif tag names](http://www.sno.phy.queensu.ca/~phil/exiftool/TagNames/EXIF.html)
 - [Exif tags](http://www.exiv2.org/tags.html)
 - [TIFF tags](http://www.awaresystems.be/imaging/tiff/tifftags.html)

I read the Exif 2.2 specification from cover-to-cover, at least 4 different times. It proved itself to be extremely useful.

## License
This project is released under an [MIT License](http://choosealicense.com/licenses/mit/). You can view the full license text, [here](./LICENSE.txt).