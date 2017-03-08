#n  does not work.  use nsed -n

######################################################################
# nsed -f pagebreak.sed file.txt | nsed -n -f appnote_ilitek.sed

# parse Ilitek App Note sequence. e.g.
# LCD_ILI9486_CMD(0XF2);
# LCD_ILI9486_INDEX(0x18);
# Delayms(1); // Delay 1ms

:Ilitek
# //Title line
s/^[1-9].*/\/\/ &/
# //comment to /* comment */
s/[/][/]\(.*\)/\/\*\1\*\/ /
s/_CMD_INDEX/_CMD/
s/_CMD_PAs/_INDEX/
s/_ Parameter (/_INDEX(/
/LCD_ILI9..._CMD(/b good
/Delayms(/b good
b print
{
:good
   h
   :args
   n
   s/[/][/]\(.*\)/\/\*\1\*\/ /
   s/_CMD_INDEX/_CMD/
   s/_CMD_PAs/_INDEX/
   s/_ Parameter (/_INDEX(/
   # append any data to Hold space
   /LCD_ILI9..._INDEX(/{
      H 
      b args
   }
   /^$/b args
   x
   # parse command byte to (0xNN),
   s/LCD_ILI9..._CMD(\([^)]+\)/    (\1)/
   # parse data byte to 0xNN,
   s/\nLCD_ILI9..._INDEX(//g
   # parse delay times
   s/Delayms(\(.+\));/    TFTLCD_DELAY8, \1, /
   s/)\;/,/g
   s/0X/0x/g
   s/,;/,/
   p
   x
   b Ilitek
}
:print
p

:end