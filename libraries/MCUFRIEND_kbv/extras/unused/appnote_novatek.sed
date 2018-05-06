#n  does not work.  use nsed -n

######################################################################
# nsed -f appnote_novatek.sed inputfile
# produce output in: init_sequence.out
# still requires removing some garbage.  
# adding array declaration, inserting argument count on each line.

# parse Novatek App Note sequence. e.g.
# Lcd_Write_Com(0XF2);
# Lcd_Write_Data(0x18);
# delay(100);

:Novatek
# trim any leading, trailing whitespace. Line scope comments
s/^[\t ]*//
s/[\t ]*$//
s/[\t ]*[/][/]\(.*\)/ \/\*\1\*\/ /
# block start
/Lcd_Write_Com(/b good
/delay(/b good
b print
{
:good
   h
   :args
   n
   s/^[\t ]*//
   s/[\t ]*$//
   s/[\t ]*[/][/]\(.*\)/ \/\*\1\*\/ /
   # append any data to Hold space
   /Lcd_Write_Data(/{
      H 
      b args
   }
   /^$/b args
   x
   # trim (   0xNN   ) to (0xNN)
   s/( */(/g
   s/ *)/)/g
   # parse command byte to (0xNN),
   s/Lcd_Write_Com(\([^)]+\)/    (\1)/
   # parse data byte to 0xNN,
   s/\nLcd_Write_Data(//g
   # parse delay times
   s/delay(\(.+\));/    TFTLCD_DELAY8, \1, /
   s/) *\;/,/g
   s/0X/0x/g
   s/,;/,/
   winit_sequence.out   
   x
   b Novatek
}
:print
:end
