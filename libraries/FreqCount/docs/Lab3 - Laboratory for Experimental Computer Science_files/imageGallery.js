// globals
var gImages = new Array();
var currentImage = 0;
var standardWidth = '928px'; 
// init gallery
function initGallery(title, imgArray){
	// reset currentImage
	currentImage = 0;
	// fill images array
	gImages = imgArray;
	// set standard with of image gallery containter
	$('imageGalleryContainer').setStyle('width', standardWidth);
	//
	// build html code for meta info container //
	//
	// title
	var metaInfoCode = '<ul><li><span class="metaInfoText">'+title+'</span></li></ul>';
	// fill meta info container with code
	$('metaInfoContainer').set({html: metaInfoCode});
	// 
	// build html code for pagination container //
	//
	// reset html code
	var paginationCode = "";
	// do this just if there are more than one image
	if(gImages.length > 1){
		// add text
		paginationCode = "<di>Images: ";
		// show first image
		paginationCode += '<a href="javascript:void(0)" onclick="loadImage(0)" class="firstImage" title="first image">&laquo; </a>';
		// show prev image function
		paginationCode += '<a href="javascript:void(0)" onclick="loadPrevImage()" class="prevNextImage" title="previous image">&#8249; </a>';
		// pagination with href to js function
		for(i=0; i<gImages.length; i++){
			// pageination number one higher than counter
			tempNumber = i+1;
			// html code
			paginationCode += '<a href="javascript:void(0)" onclick="loadImage('+i+')" class="paginationLink" id="image'+i+'" title="view image '+(i+1)+'">'+tempNumber+'</a>';
			// add ',' if not last one
			if(i<gImages.length-1){
				paginationCode += ', ';
			}
		}
		// show next image function
		paginationCode += '<a href="javascript:void(0)" onclick="loadNextImage()" class="prevNextImage" title="next image"> &#8250;</a>';
		// show last image
		paginationCode += '<a href="javascript:void(0)" onclick="loadImage('+(gImages.length-1)+')" class="lastImage" title="last image"> &raquo;</a></div>';
		// fill image gallery container with html code
		$('paginationContainer').set({html: paginationCode});
		// show pagination container if there are more than one image
		$('paginationContainer').setStyle('visibility','visible');
	}else{
		// hide pagination container if just one image
		$('paginationContainer').setStyle('visibility','hidden');
	}
	// load first image in image container
	loadImage(0);
	// show image gallery
	showImageGallery(true);
	// resize
	resizeOverlay();
}
// load image
function loadImage(imageID){
	// do this just if there are more than one image
	if(gImages.length > 1){
		// reset style of old pagination href
		$("image"+currentImage).setStyle('font-weight', 'normal');
		$("image"+currentImage).setStyle('color', '#333');
		// set style of current pagination href
		$("image"+imageID).setStyle('font-weight', 'bold');
		$("image"+imageID).setStyle('color', '#000');
	}
	// set current image
	currentImage = imageID;
	// add class with loading gif
	$('imageGalleryContainer').addClass('imageGalleryLoading');
	// hide old image
	$('imageContainer').setStyle('visibility', 'hidden');
	// hide/show meta info container
	/*if(currentImage == 0){
		$('metaInfoContainer').setStyle('visibility','visible');
	}else{
		$('metaInfoContainer').setStyle('visibility','hidden');
	}*/
	// load new image
	var newImage = new Asset.images([gImages[imageID]], { 
		// loading completed
	    onComplete: function(){ 
			// remove class with loading gif
			$('imageGalleryContainer').removeClass('imageGalleryLoading');
			// set width + height of image gallery container
			$('imageGalleryContainer').setStyle('width', newImage[0].width);
			$('imageGalleryContainer').setStyle('height', newImage[0].height);
			// get all elements inside image container
			var lastImage = $('imageContainer').getChildren();
			// check if there are already images
			if(lastImage.length > 0){
				// replace image
				newImage[0].replaces(lastImage[0]);
			}else{
				// create new image
				$('imageContainer').grab(newImage[0]);
			}
			// add click event
			newImage[0].addEvent('click',loadNextImage);
			// show new image
			// just if image gallery container is visible
			if($('imageGalleryContainer').getStyle('visibility') =='visible'){
				$('imageContainer').setStyle('visibility', 'visible');
			}
	    }
	}); 
}
// load prev next image
function loadPrevImage(){
	// set currentImage
	if(currentImage == 0){
		tempImageID = gImages.length-1;
	}else{
		tempImageID = currentImage-1;
	}
	// load Image
	loadImage(tempImageID);
}
function loadNextImage(){
	// set currentImage
	if(currentImage == gImages.length-1){
		tempImageID = 0;
	}else{
		tempImageID = currentImage+1;
	}
	// load Image
	loadImage(tempImageID);
}
// show image gallery
function showImageGallery(booleanState){
	// reset position
	var scrollTop = $(window).getScroll().y;
	$('imageGalleryContainer').setStyle('top', scrollTop+24);
	// visible image container + opacity overlay
	if(booleanState == true){
		$('imageGalleryOverlay').setStyle('visibility', 'visible');
		$('imageGalleryContainer').setStyle('visibility', 'visible');
	}else{
		// just if image gallery container is visible
		if($('imageGalleryContainer').getStyle('visibility') =='visible'){
			$('imageGalleryOverlay').setStyle('visibility', 'hidden');
			$('imageGalleryContainer').setStyle('visibility', 'hidden');
			$('imageContainer').setStyle('visibility', 'hidden');
			$('paginationContainer').setStyle('visibility','hidden');
		}
	}
}
// resize overlay
function resizeOverlay(){
	// overlay
	if($('imageGalleryOverlay').getStyle('visibility') == 'hidden'){ return; };//resize only if visible
	$('imageGalleryOverlay').setStyles({top: window.getScrollTop(), height: window.getHeight()});
}