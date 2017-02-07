/*
 * This code searches for all the <script type="application/processing">
 * in your page and loads each script inside a canvas element (which is created and added after the script element).
 * It is useful to smooth the process of adding Processing code in your page and starting
 * the Processing.js engine.
 */ 

if ( window.addEventListener ) {
	window.addEventListener("load", function() {
		var scripts = document.getElementsByTagName("script");
		
		for ( var i = 0; i < scripts.length; i++ ) {
			if ( scripts[i].type == "application/processing" ) {
				var width = 200;
				var height = 200;
				// if Processing sketch has size set, find it so we can size the canvas appropriately
				var reSize = /[^\.]size\( *(\d+), *(\d+) *\) *\;/;
				var reMatch = reSize.exec(scripts[i].text);
				if (reMatch) {
					width = reMatch[1];
					height = reMatch[2];
				}
				var canvas = jQuery("<canvas width='"+width+"' height='"+height+"'></canvas>").get(0);
				jQuery(scripts[i]).after(canvas);
				if (canvas) {
					try {
						new Processing(canvas, scripts[i].text);
					} catch (e) {
						alert("There appears to be a problem with the Processing code...\n\n " + e.name + "\n\n" + e.message);
					}
				}
			}
		}
	}, false);
}
