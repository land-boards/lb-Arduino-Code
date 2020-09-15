#n  does not work.  use nsed -n

######################################################################
# nsed -f pagebreak.sed file.txt | nsed -n -f appnote_himax.sed

# copy-paste Ilitek App Note examples to xxx.txt
# ditto Renesas, Himax, ...
# or just pipe UTFT initlcd.h through

# parse Ilitek App Note sequence. e.g.
# LCD_ILI9486_CMD(0XF2);
# LCD_ILI9486_INDEX(0x18);
# Delayms(1); // Delay 1ms

# parse GalaxyCore App Note sequence. e.g.
# LCD_ GC9102_CMD(0XF2);
# LCD_ GC9102_DATA(0x18);
# delayms(1); // Delay 1ms

# parse Himax App Note sequence. e.g.
# Set_NOKIA_8B_CMD(0XF2);
# Set_NOKIA_8B_PA(0x18);
# DelayX1ms(1); // Delay 1ms

# parse Renesas App Note sequence. e.g.
# {setc, 0x000F2}
# {setp, 0x00018}
# {time, 0040,ms}

# parse UTFT sequence. e.g.
# LCD_Write_COM(0XF2);
# LCD_Write_DATA(0x18);
# delay(1); // Delay 1ms

# parse EastRising sequence. e.g.
# Write_Cmd(0XF2);
# Write_Cmd_Data(0x18);
# delayms(1); // Delay 1ms

:Ilitek
# remove leading white space
s/^[ 	]*//
# //comment// to //comment
s/----\/\/$/----/
# //comment to /* comment */
s/[/][/]\(.*\)/\/\*\1\*\/ /
# change to consistent CMD syntax
s/LCD_ILI9..._CMD_INDEX/LCD_Write_COM/
s/LCD_ILI9..._CMD/LCD_Write_COM/
s/LCD_ GC9102_CMD/LCD_Write_COM/
s/r61581_cmd/LCD_Write_COM/
s/LV_DRV_DELAY_MS/delay/
s/LCD_Write_COM_DATA(\(.*\),\(.*\));/  (\1), 1, \2, /
s/IO.writeCommandTransaction/LCD_Write_COM/
s/Delayms/delay/
s/Set_NOKIA_8B_CMD/LCD_Write_COM/
s/DelayX1ms/delay/
s/Lcd_Write_Com/LCD_Write_COM/
s/lcdWriteReg(0x00/LCD_Write_COM(0x/
s/writecommand/LCD_Write_COM/
s/{setc,.* 0x000\(..\)}/LCD_Write_COM(0x\1);/
s/{time, 0*\(.*\),ms}/delay(\1);/
s/delayms/delay/
s/GUI_Delay/delay/
s/Write_Cmd_Data/LCD_Write_DATA/
s/Write_Cmd/LCD_Write_COM/
s/lcdWriteData(0x00/LCD_Write_DATA(0x/
s/LCD_WR_REG(/LCD_Write_COM(/
s/LCD_Write_COM *(/LCD_Write_COM(/
/LCD_Write_COM(/b good
/delay(/b good
b print
{
:good
   h
   :args
   n
   s/^[ 	]*//
   s/[ 	]*\/\/[VP][0-9]+$//
   s/[/][/]\(.*\)/ \/\*\1\*\/ /
   s/LCD_ILI9..._CMD_PAs/LCD_Write_DATA/
   s/LCD_ILI9..._INDEX/LCD_Write_DATA/
   s/LCD_ILI9..._ Parameter/LCD_Write_DATA/
   s/LCD_ GC9102_DATA/LCD_Write_DATA/
   s/r61581_data/LCD_Write_DATA/
   s/IO.writeDataTransaction/LCD_Write_DATA/
   s/Set_NOKIA_8B_PA/LCD_Write_DATA/
   s/DelayX1ms/delay/
   s/{setp,.* 0x000\(..\)}/LCD_Write_DATA(0x\1);/
   s/{setp,.* 0x00\(...\)}/LCD_Write_DATA(0x\1);/
#   s/{time, 0*\(.*\),ms}/delay(\1)/
   s/LCD_Write_DATA_8/LCD_Write_DATA/
   s/Lcd_Write_Data/LCD_Write_DATA/
   s/lcdWriteData(0x00/LCD_Write_DATA(0x/
   s/writedata/LCD_Write_DATA/
   s/delayms/delay/
   s/Write_Cmd_Data/LCD_Write_DATA/
   s/LCD_WR_DATA(/LCD_Write_DATA(/
   s/LCD_Write_DATA *(/LCD_Write_DATA(/
   #kludges for inconsistent syntax in Ilitek PDF
   s/;)$/);/
   s/)$/);/
   s/;;/;/
   # append any data to Hold space
   /LCD_Write_DATA(/{
      H 
      b args
   }
   /^$/b args
   x
   # parse command byte to (0xNN),
   s/LCD_Write_COM(\([^)]+\)/    (\1)/
   s/(0[xX]00\(..\))/(0x\1)/
   # parse data byte to 0xNN,
   s/\nLCD_Write_DATA(//g
   # parse delay times
   s/delay(\(.+\));/    TFTLCD_DELAY8, \1, /
   s/)\;/,/g
   s/0X/0x/g
   s/0x,/0x00,/g
   s/;,/,/
   w 9806.out
   # attempt to calculate number of parameters. show #ERROR# if > 16
   /0x..),.*,.*,.*,.*,.*,.*,.*,.*,.*,.*,.*,.*,.*,.*,.*,.*,.*,/s/),/),#ERROR#,/
   t counted
   /0x..),.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,/s/),/),16,/
   t counted
   /0x..),.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,/s/),/),15,/
   t counted
   /0x..),.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,/s/),/),14,/
   t counted
   /0x..),.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,/s/),/),13,/
   t counted
   /0x..),.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,/s/),/),12,/
   t counted
   /0x..),.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,/s/),/),11,/
   t counted
   /0x..),.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,/s/),/),10,/
   t counted
   /0x..),.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,/s/),/), 9,/
   t counted
   /0x..),.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,/s/),/), 8,/
   t counted
   /0x..),.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,/s/),/), 7,/
   t counted
   /0x..),.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,/s/),/), 6,/
   t counted
   /0x..),.*0x..,.*0x..,.*0x..,.*0x..,.*0x..,/s/),/), 5,/
   t counted
   /0x..),.*0x..,.*0x..,.*0x..,.*0x..,/s/),/), 4,/
   t counted
   /0x..),.*0x..,.*0x..,.*0x..,/s/),/), 3,/
   t counted
   /0x..),.*0x..,.*0x..,/s/),/), 2,/
   t counted
   /0x..),.*0x..,/s/),/), 1,/
   t counted
   /0x..),/s/),/), 0,/
:counted
   # life is simpler with multiple whitespace reduced to single space
   s/[ 	]+/ /g
   s/ $//   
   #/(0x2C)/p
   # attempt to move first comment to end of line
   s/\((0x..),[ 1][0-9],\) \/\*\([^*]*\)\*\/ \(.*\)/\1 \3	\/\/\2/
   #s/\((0x..),[ 1][0-9],\) \(\/\*[^*]*\*\/\) \(.*\)/\1 \3	\2/
   #/0x..),[ 1][0-9],/s/ *\(\/\*[^*]*\*\/\) *\(.*\)/ \2 \1/
   p
   x
   b Ilitek
}
:print
s/^[Vv]oid \(.*\)_Initial.*(void)/const unsigned char \1[] =/
s/^void LCD_Initial_\(.*\)(void)/const unsigned char \1[] =/
s/^void \(.*\)::init()/const unsigned char \1[] =/
s/^}$/};/
p

:end
