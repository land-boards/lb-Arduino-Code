



<!DOCTYPE html>
<html>
<head>
 <link rel="icon" type="image/vnd.microsoft.icon" href="http://www.gstatic.com/codesite/ph/images/phosting.ico">
 
 
 <script type="text/javascript">
 
 
 
 
 var codesite_token = null;
 
 
 var CS_env = {"profileUrl":null,"token":null,"assetHostPath":"http://www.gstatic.com/codesite/ph","domainName":null,"assetVersionPath":"http://www.gstatic.com/codesite/ph/16216231599268812631","projectHomeUrl":"/p/neuroelec","relativeBaseUrl":"","projectName":"neuroelec","loggedInUserEmail":null};
 var _gaq = _gaq || [];
 _gaq.push(
 ['siteTracker._setAccount', 'UA-18071-1'],
 ['siteTracker._trackPageview']);
 
 _gaq.push(
 ['projectTracker._setAccount', 'UA-143071-8'],
 ['projectTracker._trackPageview']);
 
 
 </script>
 
 
 <title>ffft.S - 
 neuroelec -
 
 
 open source library for arduino - Google Project Hosting
 </title>
 <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" >
 <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1" >
 
 <meta name="ROBOTS" content="NOARCHIVE">
 
 <link type="text/css" rel="stylesheet" href="http://www.gstatic.com/codesite/ph/16216231599268812631/css/core.css">
 
 <link type="text/css" rel="stylesheet" href="http://www.gstatic.com/codesite/ph/16216231599268812631/css/ph_detail.css" >
 
 
 <link type="text/css" rel="stylesheet" href="http://www.gstatic.com/codesite/ph/16216231599268812631/css/d_sb.css" >
 
 
 
<!--[if IE]>
 <link type="text/css" rel="stylesheet" href="http://www.gstatic.com/codesite/ph/16216231599268812631/css/d_ie.css" >
<![endif]-->
 <style type="text/css">
 .menuIcon.off { background: no-repeat url(http://www.gstatic.com/codesite/ph/images/dropdown_sprite.gif) 0 -42px }
 .menuIcon.on { background: no-repeat url(http://www.gstatic.com/codesite/ph/images/dropdown_sprite.gif) 0 -28px }
 .menuIcon.down { background: no-repeat url(http://www.gstatic.com/codesite/ph/images/dropdown_sprite.gif) 0 0; }
 
 
 
  tr.inline_comment {
 background: #fff;
 vertical-align: top;
 }
 div.draft, div.published {
 padding: .3em;
 border: 1px solid #999; 
 margin-bottom: .1em;
 font-family: arial, sans-serif;
 max-width: 60em;
 }
 div.draft {
 background: #ffa;
 } 
 div.published {
 background: #e5ecf9;
 }
 div.published .body, div.draft .body {
 padding: .5em .1em .1em .1em;
 max-width: 60em;
 white-space: pre-wrap;
 white-space: -moz-pre-wrap;
 white-space: -pre-wrap;
 white-space: -o-pre-wrap;
 word-wrap: break-word;
 font-size: 1em;
 }
 div.draft .actions {
 margin-left: 1em;
 font-size: 90%;
 }
 div.draft form {
 padding: .5em .5em .5em 0;
 }
 div.draft textarea, div.published textarea {
 width: 95%;
 height: 10em;
 font-family: arial, sans-serif;
 margin-bottom: .5em;
 }

 
 .nocursor, .nocursor td, .cursor_hidden, .cursor_hidden td {
 background-color: white;
 height: 2px;
 }
 .cursor, .cursor td {
 background-color: darkblue;
 height: 2px;
 display: '';
 }
 
 
.list {
 border: 1px solid white;
 border-bottom: 0;
}

 
 </style>
</head>
<body class="t4">
<script type="text/javascript">
 (function() {
 var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
 ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
 (document.getElementsByTagName('head')[0] || document.getElementsByTagName('body')[0]).appendChild(ga);
 })();
</script>
<div class="headbg">

 <div id="gaia">
 

 <span>
 
 <a href="#" id="projects-dropdown" onclick="return false;"><u>My favorites</u> <small>&#9660;</small></a>
 | <a href="https://www.google.com/accounts/ServiceLogin?service=code&amp;ltmpl=phosting&amp;continue=http%3A%2F%2Fcode.google.com%2Fp%2Fneuroelec%2Fsource%2Fbrowse%2Ftrunk%2Flibraries%2FArduino%25201.0%2Fffft%2Fffft.S&amp;followup=http%3A%2F%2Fcode.google.com%2Fp%2Fneuroelec%2Fsource%2Fbrowse%2Ftrunk%2Flibraries%2FArduino%25201.0%2Fffft%2Fffft.S" onclick="_CS_click('/gb/ph/signin');"><u>Sign in</u></a>
 
 </span>

 </div>

 <div class="gbh" style="left: 0pt;"></div>
 <div class="gbh" style="right: 0pt;"></div>
 
 
 <div style="height: 1px"></div>
<!--[if lte IE 7]>
<div style="text-align:center;">
Your version of Internet Explorer is not supported. Try a browser that
contributes to open source, such as <a href="http://www.firefox.com">Firefox</a>,
<a href="http://www.google.com/chrome">Google Chrome</a>, or
<a href="http://code.google.com/chrome/chromeframe/">Google Chrome Frame</a>.
</div>
<![endif]-->




 <table style="padding:0px; margin: 0px 0px 10px 0px; width:100%" cellpadding="0" cellspacing="0"
 itemscope itemtype="http://schema.org/CreativeWork">
 <tr style="height: 58px;">
 
 <td id="plogo">
 <link itemprop="url" href="/p/neuroelec">
 <a href="/p/neuroelec/">
 
 <img src="http://www.gstatic.com/codesite/ph/images/defaultlogo.png" alt="Logo" itemprop="image">
 
 </a>
 </td>
 
 <td style="padding-left: 0.5em">
 
 <div id="pname">
 <a href="/p/neuroelec/"><span itemprop="name">neuroelec</span></a>
 </div>
 
 <div id="psum">
 <a id="project_summary_link"
 href="/p/neuroelec/"><span itemprop="description">open source library for arduino</span></a>
 
 </div>
 
 
 </td>
 <td style="white-space:nowrap;text-align:right; vertical-align:bottom;">
 
 <form action="/hosting/search">
 <input size="30" name="q" value="" type="text">
 
 <input type="submit" name="projectsearch" value="Search projects" >
 </form>
 
 </tr>
 </table>

</div>

 
<div id="mt" class="gtb"> 
 <a href="/p/neuroelec/" class="tab ">Project&nbsp;Home</a>
 
 
 
 
 <a href="/p/neuroelec/downloads/list" class="tab ">Downloads</a>
 
 
 
 
 
 <a href="/p/neuroelec/w/list" class="tab ">Wiki</a>
 
 
 
 
 
 <a href="/p/neuroelec/issues/list"
 class="tab ">Issues</a>
 
 
 
 
 
 <a href="/p/neuroelec/source/checkout"
 class="tab active">Source</a>
 
 
 
 
 
 <div class=gtbc></div>
</div>
<table cellspacing="0" cellpadding="0" width="100%" align="center" border="0" class="st">
 <tr>
 
 
 
 
 
 
 <td class="subt">
 <div class="st2">
 <div class="isf">
 
 


 <span class="inst1"><a href="/p/neuroelec/source/checkout">Checkout</a></span> &nbsp;
 <span class="inst2"><a href="/p/neuroelec/source/browse/">Browse</a></span> &nbsp;
 <span class="inst3"><a href="/p/neuroelec/source/list">Changes</a></span> &nbsp;
 
 &nbsp;
 
 <form action="/p/neuroelec/source/search" method="get" style="display:inline"
 onsubmit="document.getElementById('codesearchq').value = document.getElementById('origq').value">
 <input type="hidden" name="q" id="codesearchq" value="">
 <input type="text" maxlength="2048" size="38" id="origq" name="origq" value="" title="Google Code Search" style="font-size:92%">&nbsp;<input type="submit" value="Search Trunk" name="btnG" style="font-size:92%">
 
 
 
 
 
 
 </form>
 </div>
</div>

 </td>
 
 
 
 <td align="right" valign="top" class="bevel-right"></td>
 </tr>
</table>


<script type="text/javascript">
 var cancelBubble = false;
 function _go(url) { document.location = url; }
</script>
<div id="maincol"
 
>

 
<!-- IE -->




<div class="expand">
<div id="colcontrol">
<style type="text/css">
 #file_flipper { white-space: nowrap; padding-right: 2em; }
 #file_flipper.hidden { display: none; }
 #file_flipper .pagelink { color: #0000CC; text-decoration: underline; }
 #file_flipper #visiblefiles { padding-left: 0.5em; padding-right: 0.5em; }
</style>
<table id="nav_and_rev" class="list"
 cellpadding="0" cellspacing="0" width="100%">
 <tr>
 
 <td nowrap="nowrap" class="src_crumbs src_nav" width="33%">
 <strong class="src_nav">Source path:&nbsp;</strong>
 <span id="crumb_root">
 
 <a href="/p/neuroelec/source/browse/">svn</a>/&nbsp;</span>
 <span id="crumb_links" class="ifClosed"><a href="/p/neuroelec/source/browse/trunk/">trunk</a><span class="sp">/&nbsp;</span><a href="/p/neuroelec/source/browse/trunk/libraries/">libraries</a><span class="sp">/&nbsp;</span><a href="/p/neuroelec/source/browse/trunk/libraries/Arduino+1.0/">Arduino 1.0</a><span class="sp">/&nbsp;</span><a href="/p/neuroelec/source/browse/trunk/libraries/Arduino+1.0/ffft/">ffft</a><span class="sp">/&nbsp;</span>ffft.S</span>
 
 

 </td>
 
 
 <td nowrap="nowrap" width="33%" align="right">
 <table cellpadding="0" cellspacing="0" style="font-size: 100%"><tr>
 
 
 <td class="flipper"><b>r23</b></td>
 
 </tr></table>
 </td> 
 </tr>
</table>

<div class="fc">
 
 
 
<style type="text/css">
.undermouse span {
 background-image: url(http://www.gstatic.com/codesite/ph/images/comments.gif); }
</style>
<table class="opened" id="review_comment_area"
><tr>
<td id="nums">
<pre><table width="100%"><tr class="nocursor"><td></td></tr></table></pre>
<pre><table width="100%" id="nums_table_0"><tr id="gr_svn23_1"

><td id="1"><a href="#1">1</a></td></tr
><tr id="gr_svn23_2"

><td id="2"><a href="#2">2</a></td></tr
><tr id="gr_svn23_3"

><td id="3"><a href="#3">3</a></td></tr
><tr id="gr_svn23_4"

><td id="4"><a href="#4">4</a></td></tr
><tr id="gr_svn23_5"

><td id="5"><a href="#5">5</a></td></tr
><tr id="gr_svn23_6"

><td id="6"><a href="#6">6</a></td></tr
><tr id="gr_svn23_7"

><td id="7"><a href="#7">7</a></td></tr
><tr id="gr_svn23_8"

><td id="8"><a href="#8">8</a></td></tr
><tr id="gr_svn23_9"

><td id="9"><a href="#9">9</a></td></tr
><tr id="gr_svn23_10"

><td id="10"><a href="#10">10</a></td></tr
><tr id="gr_svn23_11"

><td id="11"><a href="#11">11</a></td></tr
><tr id="gr_svn23_12"

><td id="12"><a href="#12">12</a></td></tr
><tr id="gr_svn23_13"

><td id="13"><a href="#13">13</a></td></tr
><tr id="gr_svn23_14"

><td id="14"><a href="#14">14</a></td></tr
><tr id="gr_svn23_15"

><td id="15"><a href="#15">15</a></td></tr
><tr id="gr_svn23_16"

><td id="16"><a href="#16">16</a></td></tr
><tr id="gr_svn23_17"

><td id="17"><a href="#17">17</a></td></tr
><tr id="gr_svn23_18"

><td id="18"><a href="#18">18</a></td></tr
><tr id="gr_svn23_19"

><td id="19"><a href="#19">19</a></td></tr
><tr id="gr_svn23_20"

><td id="20"><a href="#20">20</a></td></tr
><tr id="gr_svn23_21"

><td id="21"><a href="#21">21</a></td></tr
><tr id="gr_svn23_22"

><td id="22"><a href="#22">22</a></td></tr
><tr id="gr_svn23_23"

><td id="23"><a href="#23">23</a></td></tr
><tr id="gr_svn23_24"

><td id="24"><a href="#24">24</a></td></tr
><tr id="gr_svn23_25"

><td id="25"><a href="#25">25</a></td></tr
><tr id="gr_svn23_26"

><td id="26"><a href="#26">26</a></td></tr
><tr id="gr_svn23_27"

><td id="27"><a href="#27">27</a></td></tr
><tr id="gr_svn23_28"

><td id="28"><a href="#28">28</a></td></tr
><tr id="gr_svn23_29"

><td id="29"><a href="#29">29</a></td></tr
><tr id="gr_svn23_30"

><td id="30"><a href="#30">30</a></td></tr
><tr id="gr_svn23_31"

><td id="31"><a href="#31">31</a></td></tr
><tr id="gr_svn23_32"

><td id="32"><a href="#32">32</a></td></tr
><tr id="gr_svn23_33"

><td id="33"><a href="#33">33</a></td></tr
><tr id="gr_svn23_34"

><td id="34"><a href="#34">34</a></td></tr
><tr id="gr_svn23_35"

><td id="35"><a href="#35">35</a></td></tr
><tr id="gr_svn23_36"

><td id="36"><a href="#36">36</a></td></tr
><tr id="gr_svn23_37"

><td id="37"><a href="#37">37</a></td></tr
><tr id="gr_svn23_38"

><td id="38"><a href="#38">38</a></td></tr
><tr id="gr_svn23_39"

><td id="39"><a href="#39">39</a></td></tr
><tr id="gr_svn23_40"

><td id="40"><a href="#40">40</a></td></tr
><tr id="gr_svn23_41"

><td id="41"><a href="#41">41</a></td></tr
><tr id="gr_svn23_42"

><td id="42"><a href="#42">42</a></td></tr
><tr id="gr_svn23_43"

><td id="43"><a href="#43">43</a></td></tr
><tr id="gr_svn23_44"

><td id="44"><a href="#44">44</a></td></tr
><tr id="gr_svn23_45"

><td id="45"><a href="#45">45</a></td></tr
><tr id="gr_svn23_46"

><td id="46"><a href="#46">46</a></td></tr
><tr id="gr_svn23_47"

><td id="47"><a href="#47">47</a></td></tr
><tr id="gr_svn23_48"

><td id="48"><a href="#48">48</a></td></tr
><tr id="gr_svn23_49"

><td id="49"><a href="#49">49</a></td></tr
><tr id="gr_svn23_50"

><td id="50"><a href="#50">50</a></td></tr
><tr id="gr_svn23_51"

><td id="51"><a href="#51">51</a></td></tr
><tr id="gr_svn23_52"

><td id="52"><a href="#52">52</a></td></tr
><tr id="gr_svn23_53"

><td id="53"><a href="#53">53</a></td></tr
><tr id="gr_svn23_54"

><td id="54"><a href="#54">54</a></td></tr
><tr id="gr_svn23_55"

><td id="55"><a href="#55">55</a></td></tr
><tr id="gr_svn23_56"

><td id="56"><a href="#56">56</a></td></tr
><tr id="gr_svn23_57"

><td id="57"><a href="#57">57</a></td></tr
><tr id="gr_svn23_58"

><td id="58"><a href="#58">58</a></td></tr
><tr id="gr_svn23_59"

><td id="59"><a href="#59">59</a></td></tr
><tr id="gr_svn23_60"

><td id="60"><a href="#60">60</a></td></tr
><tr id="gr_svn23_61"

><td id="61"><a href="#61">61</a></td></tr
><tr id="gr_svn23_62"

><td id="62"><a href="#62">62</a></td></tr
><tr id="gr_svn23_63"

><td id="63"><a href="#63">63</a></td></tr
><tr id="gr_svn23_64"

><td id="64"><a href="#64">64</a></td></tr
><tr id="gr_svn23_65"

><td id="65"><a href="#65">65</a></td></tr
><tr id="gr_svn23_66"

><td id="66"><a href="#66">66</a></td></tr
><tr id="gr_svn23_67"

><td id="67"><a href="#67">67</a></td></tr
><tr id="gr_svn23_68"

><td id="68"><a href="#68">68</a></td></tr
><tr id="gr_svn23_69"

><td id="69"><a href="#69">69</a></td></tr
><tr id="gr_svn23_70"

><td id="70"><a href="#70">70</a></td></tr
><tr id="gr_svn23_71"

><td id="71"><a href="#71">71</a></td></tr
><tr id="gr_svn23_72"

><td id="72"><a href="#72">72</a></td></tr
><tr id="gr_svn23_73"

><td id="73"><a href="#73">73</a></td></tr
><tr id="gr_svn23_74"

><td id="74"><a href="#74">74</a></td></tr
><tr id="gr_svn23_75"

><td id="75"><a href="#75">75</a></td></tr
><tr id="gr_svn23_76"

><td id="76"><a href="#76">76</a></td></tr
><tr id="gr_svn23_77"

><td id="77"><a href="#77">77</a></td></tr
><tr id="gr_svn23_78"

><td id="78"><a href="#78">78</a></td></tr
><tr id="gr_svn23_79"

><td id="79"><a href="#79">79</a></td></tr
><tr id="gr_svn23_80"

><td id="80"><a href="#80">80</a></td></tr
><tr id="gr_svn23_81"

><td id="81"><a href="#81">81</a></td></tr
><tr id="gr_svn23_82"

><td id="82"><a href="#82">82</a></td></tr
><tr id="gr_svn23_83"

><td id="83"><a href="#83">83</a></td></tr
><tr id="gr_svn23_84"

><td id="84"><a href="#84">84</a></td></tr
><tr id="gr_svn23_85"

><td id="85"><a href="#85">85</a></td></tr
><tr id="gr_svn23_86"

><td id="86"><a href="#86">86</a></td></tr
><tr id="gr_svn23_87"

><td id="87"><a href="#87">87</a></td></tr
><tr id="gr_svn23_88"

><td id="88"><a href="#88">88</a></td></tr
><tr id="gr_svn23_89"

><td id="89"><a href="#89">89</a></td></tr
><tr id="gr_svn23_90"

><td id="90"><a href="#90">90</a></td></tr
><tr id="gr_svn23_91"

><td id="91"><a href="#91">91</a></td></tr
><tr id="gr_svn23_92"

><td id="92"><a href="#92">92</a></td></tr
><tr id="gr_svn23_93"

><td id="93"><a href="#93">93</a></td></tr
><tr id="gr_svn23_94"

><td id="94"><a href="#94">94</a></td></tr
><tr id="gr_svn23_95"

><td id="95"><a href="#95">95</a></td></tr
><tr id="gr_svn23_96"

><td id="96"><a href="#96">96</a></td></tr
><tr id="gr_svn23_97"

><td id="97"><a href="#97">97</a></td></tr
><tr id="gr_svn23_98"

><td id="98"><a href="#98">98</a></td></tr
><tr id="gr_svn23_99"

><td id="99"><a href="#99">99</a></td></tr
><tr id="gr_svn23_100"

><td id="100"><a href="#100">100</a></td></tr
><tr id="gr_svn23_101"

><td id="101"><a href="#101">101</a></td></tr
><tr id="gr_svn23_102"

><td id="102"><a href="#102">102</a></td></tr
><tr id="gr_svn23_103"

><td id="103"><a href="#103">103</a></td></tr
><tr id="gr_svn23_104"

><td id="104"><a href="#104">104</a></td></tr
><tr id="gr_svn23_105"

><td id="105"><a href="#105">105</a></td></tr
><tr id="gr_svn23_106"

><td id="106"><a href="#106">106</a></td></tr
><tr id="gr_svn23_107"

><td id="107"><a href="#107">107</a></td></tr
><tr id="gr_svn23_108"

><td id="108"><a href="#108">108</a></td></tr
><tr id="gr_svn23_109"

><td id="109"><a href="#109">109</a></td></tr
><tr id="gr_svn23_110"

><td id="110"><a href="#110">110</a></td></tr
><tr id="gr_svn23_111"

><td id="111"><a href="#111">111</a></td></tr
><tr id="gr_svn23_112"

><td id="112"><a href="#112">112</a></td></tr
><tr id="gr_svn23_113"

><td id="113"><a href="#113">113</a></td></tr
><tr id="gr_svn23_114"

><td id="114"><a href="#114">114</a></td></tr
><tr id="gr_svn23_115"

><td id="115"><a href="#115">115</a></td></tr
><tr id="gr_svn23_116"

><td id="116"><a href="#116">116</a></td></tr
><tr id="gr_svn23_117"

><td id="117"><a href="#117">117</a></td></tr
><tr id="gr_svn23_118"

><td id="118"><a href="#118">118</a></td></tr
><tr id="gr_svn23_119"

><td id="119"><a href="#119">119</a></td></tr
><tr id="gr_svn23_120"

><td id="120"><a href="#120">120</a></td></tr
><tr id="gr_svn23_121"

><td id="121"><a href="#121">121</a></td></tr
><tr id="gr_svn23_122"

><td id="122"><a href="#122">122</a></td></tr
><tr id="gr_svn23_123"

><td id="123"><a href="#123">123</a></td></tr
><tr id="gr_svn23_124"

><td id="124"><a href="#124">124</a></td></tr
><tr id="gr_svn23_125"

><td id="125"><a href="#125">125</a></td></tr
><tr id="gr_svn23_126"

><td id="126"><a href="#126">126</a></td></tr
><tr id="gr_svn23_127"

><td id="127"><a href="#127">127</a></td></tr
><tr id="gr_svn23_128"

><td id="128"><a href="#128">128</a></td></tr
><tr id="gr_svn23_129"

><td id="129"><a href="#129">129</a></td></tr
><tr id="gr_svn23_130"

><td id="130"><a href="#130">130</a></td></tr
><tr id="gr_svn23_131"

><td id="131"><a href="#131">131</a></td></tr
><tr id="gr_svn23_132"

><td id="132"><a href="#132">132</a></td></tr
><tr id="gr_svn23_133"

><td id="133"><a href="#133">133</a></td></tr
><tr id="gr_svn23_134"

><td id="134"><a href="#134">134</a></td></tr
><tr id="gr_svn23_135"

><td id="135"><a href="#135">135</a></td></tr
><tr id="gr_svn23_136"

><td id="136"><a href="#136">136</a></td></tr
><tr id="gr_svn23_137"

><td id="137"><a href="#137">137</a></td></tr
><tr id="gr_svn23_138"

><td id="138"><a href="#138">138</a></td></tr
><tr id="gr_svn23_139"

><td id="139"><a href="#139">139</a></td></tr
><tr id="gr_svn23_140"

><td id="140"><a href="#140">140</a></td></tr
><tr id="gr_svn23_141"

><td id="141"><a href="#141">141</a></td></tr
><tr id="gr_svn23_142"

><td id="142"><a href="#142">142</a></td></tr
><tr id="gr_svn23_143"

><td id="143"><a href="#143">143</a></td></tr
><tr id="gr_svn23_144"

><td id="144"><a href="#144">144</a></td></tr
><tr id="gr_svn23_145"

><td id="145"><a href="#145">145</a></td></tr
><tr id="gr_svn23_146"

><td id="146"><a href="#146">146</a></td></tr
><tr id="gr_svn23_147"

><td id="147"><a href="#147">147</a></td></tr
><tr id="gr_svn23_148"

><td id="148"><a href="#148">148</a></td></tr
><tr id="gr_svn23_149"

><td id="149"><a href="#149">149</a></td></tr
><tr id="gr_svn23_150"

><td id="150"><a href="#150">150</a></td></tr
><tr id="gr_svn23_151"

><td id="151"><a href="#151">151</a></td></tr
><tr id="gr_svn23_152"

><td id="152"><a href="#152">152</a></td></tr
><tr id="gr_svn23_153"

><td id="153"><a href="#153">153</a></td></tr
><tr id="gr_svn23_154"

><td id="154"><a href="#154">154</a></td></tr
><tr id="gr_svn23_155"

><td id="155"><a href="#155">155</a></td></tr
><tr id="gr_svn23_156"

><td id="156"><a href="#156">156</a></td></tr
><tr id="gr_svn23_157"

><td id="157"><a href="#157">157</a></td></tr
><tr id="gr_svn23_158"

><td id="158"><a href="#158">158</a></td></tr
><tr id="gr_svn23_159"

><td id="159"><a href="#159">159</a></td></tr
><tr id="gr_svn23_160"

><td id="160"><a href="#160">160</a></td></tr
><tr id="gr_svn23_161"

><td id="161"><a href="#161">161</a></td></tr
><tr id="gr_svn23_162"

><td id="162"><a href="#162">162</a></td></tr
><tr id="gr_svn23_163"

><td id="163"><a href="#163">163</a></td></tr
><tr id="gr_svn23_164"

><td id="164"><a href="#164">164</a></td></tr
><tr id="gr_svn23_165"

><td id="165"><a href="#165">165</a></td></tr
><tr id="gr_svn23_166"

><td id="166"><a href="#166">166</a></td></tr
><tr id="gr_svn23_167"

><td id="167"><a href="#167">167</a></td></tr
><tr id="gr_svn23_168"

><td id="168"><a href="#168">168</a></td></tr
><tr id="gr_svn23_169"

><td id="169"><a href="#169">169</a></td></tr
><tr id="gr_svn23_170"

><td id="170"><a href="#170">170</a></td></tr
><tr id="gr_svn23_171"

><td id="171"><a href="#171">171</a></td></tr
><tr id="gr_svn23_172"

><td id="172"><a href="#172">172</a></td></tr
><tr id="gr_svn23_173"

><td id="173"><a href="#173">173</a></td></tr
><tr id="gr_svn23_174"

><td id="174"><a href="#174">174</a></td></tr
><tr id="gr_svn23_175"

><td id="175"><a href="#175">175</a></td></tr
><tr id="gr_svn23_176"

><td id="176"><a href="#176">176</a></td></tr
><tr id="gr_svn23_177"

><td id="177"><a href="#177">177</a></td></tr
><tr id="gr_svn23_178"

><td id="178"><a href="#178">178</a></td></tr
><tr id="gr_svn23_179"

><td id="179"><a href="#179">179</a></td></tr
><tr id="gr_svn23_180"

><td id="180"><a href="#180">180</a></td></tr
><tr id="gr_svn23_181"

><td id="181"><a href="#181">181</a></td></tr
><tr id="gr_svn23_182"

><td id="182"><a href="#182">182</a></td></tr
><tr id="gr_svn23_183"

><td id="183"><a href="#183">183</a></td></tr
><tr id="gr_svn23_184"

><td id="184"><a href="#184">184</a></td></tr
><tr id="gr_svn23_185"

><td id="185"><a href="#185">185</a></td></tr
><tr id="gr_svn23_186"

><td id="186"><a href="#186">186</a></td></tr
><tr id="gr_svn23_187"

><td id="187"><a href="#187">187</a></td></tr
><tr id="gr_svn23_188"

><td id="188"><a href="#188">188</a></td></tr
><tr id="gr_svn23_189"

><td id="189"><a href="#189">189</a></td></tr
><tr id="gr_svn23_190"

><td id="190"><a href="#190">190</a></td></tr
><tr id="gr_svn23_191"

><td id="191"><a href="#191">191</a></td></tr
><tr id="gr_svn23_192"

><td id="192"><a href="#192">192</a></td></tr
><tr id="gr_svn23_193"

><td id="193"><a href="#193">193</a></td></tr
><tr id="gr_svn23_194"

><td id="194"><a href="#194">194</a></td></tr
><tr id="gr_svn23_195"

><td id="195"><a href="#195">195</a></td></tr
><tr id="gr_svn23_196"

><td id="196"><a href="#196">196</a></td></tr
><tr id="gr_svn23_197"

><td id="197"><a href="#197">197</a></td></tr
><tr id="gr_svn23_198"

><td id="198"><a href="#198">198</a></td></tr
><tr id="gr_svn23_199"

><td id="199"><a href="#199">199</a></td></tr
><tr id="gr_svn23_200"

><td id="200"><a href="#200">200</a></td></tr
><tr id="gr_svn23_201"

><td id="201"><a href="#201">201</a></td></tr
><tr id="gr_svn23_202"

><td id="202"><a href="#202">202</a></td></tr
><tr id="gr_svn23_203"

><td id="203"><a href="#203">203</a></td></tr
><tr id="gr_svn23_204"

><td id="204"><a href="#204">204</a></td></tr
><tr id="gr_svn23_205"

><td id="205"><a href="#205">205</a></td></tr
><tr id="gr_svn23_206"

><td id="206"><a href="#206">206</a></td></tr
><tr id="gr_svn23_207"

><td id="207"><a href="#207">207</a></td></tr
><tr id="gr_svn23_208"

><td id="208"><a href="#208">208</a></td></tr
><tr id="gr_svn23_209"

><td id="209"><a href="#209">209</a></td></tr
><tr id="gr_svn23_210"

><td id="210"><a href="#210">210</a></td></tr
><tr id="gr_svn23_211"

><td id="211"><a href="#211">211</a></td></tr
><tr id="gr_svn23_212"

><td id="212"><a href="#212">212</a></td></tr
><tr id="gr_svn23_213"

><td id="213"><a href="#213">213</a></td></tr
><tr id="gr_svn23_214"

><td id="214"><a href="#214">214</a></td></tr
><tr id="gr_svn23_215"

><td id="215"><a href="#215">215</a></td></tr
><tr id="gr_svn23_216"

><td id="216"><a href="#216">216</a></td></tr
><tr id="gr_svn23_217"

><td id="217"><a href="#217">217</a></td></tr
><tr id="gr_svn23_218"

><td id="218"><a href="#218">218</a></td></tr
><tr id="gr_svn23_219"

><td id="219"><a href="#219">219</a></td></tr
><tr id="gr_svn23_220"

><td id="220"><a href="#220">220</a></td></tr
><tr id="gr_svn23_221"

><td id="221"><a href="#221">221</a></td></tr
><tr id="gr_svn23_222"

><td id="222"><a href="#222">222</a></td></tr
><tr id="gr_svn23_223"

><td id="223"><a href="#223">223</a></td></tr
><tr id="gr_svn23_224"

><td id="224"><a href="#224">224</a></td></tr
><tr id="gr_svn23_225"

><td id="225"><a href="#225">225</a></td></tr
><tr id="gr_svn23_226"

><td id="226"><a href="#226">226</a></td></tr
><tr id="gr_svn23_227"

><td id="227"><a href="#227">227</a></td></tr
><tr id="gr_svn23_228"

><td id="228"><a href="#228">228</a></td></tr
><tr id="gr_svn23_229"

><td id="229"><a href="#229">229</a></td></tr
><tr id="gr_svn23_230"

><td id="230"><a href="#230">230</a></td></tr
><tr id="gr_svn23_231"

><td id="231"><a href="#231">231</a></td></tr
><tr id="gr_svn23_232"

><td id="232"><a href="#232">232</a></td></tr
><tr id="gr_svn23_233"

><td id="233"><a href="#233">233</a></td></tr
><tr id="gr_svn23_234"

><td id="234"><a href="#234">234</a></td></tr
><tr id="gr_svn23_235"

><td id="235"><a href="#235">235</a></td></tr
><tr id="gr_svn23_236"

><td id="236"><a href="#236">236</a></td></tr
><tr id="gr_svn23_237"

><td id="237"><a href="#237">237</a></td></tr
><tr id="gr_svn23_238"

><td id="238"><a href="#238">238</a></td></tr
><tr id="gr_svn23_239"

><td id="239"><a href="#239">239</a></td></tr
><tr id="gr_svn23_240"

><td id="240"><a href="#240">240</a></td></tr
><tr id="gr_svn23_241"

><td id="241"><a href="#241">241</a></td></tr
><tr id="gr_svn23_242"

><td id="242"><a href="#242">242</a></td></tr
><tr id="gr_svn23_243"

><td id="243"><a href="#243">243</a></td></tr
><tr id="gr_svn23_244"

><td id="244"><a href="#244">244</a></td></tr
><tr id="gr_svn23_245"

><td id="245"><a href="#245">245</a></td></tr
><tr id="gr_svn23_246"

><td id="246"><a href="#246">246</a></td></tr
><tr id="gr_svn23_247"

><td id="247"><a href="#247">247</a></td></tr
><tr id="gr_svn23_248"

><td id="248"><a href="#248">248</a></td></tr
><tr id="gr_svn23_249"

><td id="249"><a href="#249">249</a></td></tr
><tr id="gr_svn23_250"

><td id="250"><a href="#250">250</a></td></tr
><tr id="gr_svn23_251"

><td id="251"><a href="#251">251</a></td></tr
><tr id="gr_svn23_252"

><td id="252"><a href="#252">252</a></td></tr
><tr id="gr_svn23_253"

><td id="253"><a href="#253">253</a></td></tr
><tr id="gr_svn23_254"

><td id="254"><a href="#254">254</a></td></tr
><tr id="gr_svn23_255"

><td id="255"><a href="#255">255</a></td></tr
><tr id="gr_svn23_256"

><td id="256"><a href="#256">256</a></td></tr
><tr id="gr_svn23_257"

><td id="257"><a href="#257">257</a></td></tr
><tr id="gr_svn23_258"

><td id="258"><a href="#258">258</a></td></tr
><tr id="gr_svn23_259"

><td id="259"><a href="#259">259</a></td></tr
><tr id="gr_svn23_260"

><td id="260"><a href="#260">260</a></td></tr
><tr id="gr_svn23_261"

><td id="261"><a href="#261">261</a></td></tr
><tr id="gr_svn23_262"

><td id="262"><a href="#262">262</a></td></tr
><tr id="gr_svn23_263"

><td id="263"><a href="#263">263</a></td></tr
><tr id="gr_svn23_264"

><td id="264"><a href="#264">264</a></td></tr
><tr id="gr_svn23_265"

><td id="265"><a href="#265">265</a></td></tr
><tr id="gr_svn23_266"

><td id="266"><a href="#266">266</a></td></tr
><tr id="gr_svn23_267"

><td id="267"><a href="#267">267</a></td></tr
><tr id="gr_svn23_268"

><td id="268"><a href="#268">268</a></td></tr
><tr id="gr_svn23_269"

><td id="269"><a href="#269">269</a></td></tr
><tr id="gr_svn23_270"

><td id="270"><a href="#270">270</a></td></tr
><tr id="gr_svn23_271"

><td id="271"><a href="#271">271</a></td></tr
><tr id="gr_svn23_272"

><td id="272"><a href="#272">272</a></td></tr
><tr id="gr_svn23_273"

><td id="273"><a href="#273">273</a></td></tr
><tr id="gr_svn23_274"

><td id="274"><a href="#274">274</a></td></tr
><tr id="gr_svn23_275"

><td id="275"><a href="#275">275</a></td></tr
><tr id="gr_svn23_276"

><td id="276"><a href="#276">276</a></td></tr
><tr id="gr_svn23_277"

><td id="277"><a href="#277">277</a></td></tr
><tr id="gr_svn23_278"

><td id="278"><a href="#278">278</a></td></tr
><tr id="gr_svn23_279"

><td id="279"><a href="#279">279</a></td></tr
><tr id="gr_svn23_280"

><td id="280"><a href="#280">280</a></td></tr
><tr id="gr_svn23_281"

><td id="281"><a href="#281">281</a></td></tr
><tr id="gr_svn23_282"

><td id="282"><a href="#282">282</a></td></tr
><tr id="gr_svn23_283"

><td id="283"><a href="#283">283</a></td></tr
><tr id="gr_svn23_284"

><td id="284"><a href="#284">284</a></td></tr
><tr id="gr_svn23_285"

><td id="285"><a href="#285">285</a></td></tr
><tr id="gr_svn23_286"

><td id="286"><a href="#286">286</a></td></tr
><tr id="gr_svn23_287"

><td id="287"><a href="#287">287</a></td></tr
><tr id="gr_svn23_288"

><td id="288"><a href="#288">288</a></td></tr
><tr id="gr_svn23_289"

><td id="289"><a href="#289">289</a></td></tr
><tr id="gr_svn23_290"

><td id="290"><a href="#290">290</a></td></tr
><tr id="gr_svn23_291"

><td id="291"><a href="#291">291</a></td></tr
><tr id="gr_svn23_292"

><td id="292"><a href="#292">292</a></td></tr
><tr id="gr_svn23_293"

><td id="293"><a href="#293">293</a></td></tr
><tr id="gr_svn23_294"

><td id="294"><a href="#294">294</a></td></tr
><tr id="gr_svn23_295"

><td id="295"><a href="#295">295</a></td></tr
><tr id="gr_svn23_296"

><td id="296"><a href="#296">296</a></td></tr
><tr id="gr_svn23_297"

><td id="297"><a href="#297">297</a></td></tr
><tr id="gr_svn23_298"

><td id="298"><a href="#298">298</a></td></tr
><tr id="gr_svn23_299"

><td id="299"><a href="#299">299</a></td></tr
><tr id="gr_svn23_300"

><td id="300"><a href="#300">300</a></td></tr
><tr id="gr_svn23_301"

><td id="301"><a href="#301">301</a></td></tr
><tr id="gr_svn23_302"

><td id="302"><a href="#302">302</a></td></tr
><tr id="gr_svn23_303"

><td id="303"><a href="#303">303</a></td></tr
><tr id="gr_svn23_304"

><td id="304"><a href="#304">304</a></td></tr
><tr id="gr_svn23_305"

><td id="305"><a href="#305">305</a></td></tr
><tr id="gr_svn23_306"

><td id="306"><a href="#306">306</a></td></tr
><tr id="gr_svn23_307"

><td id="307"><a href="#307">307</a></td></tr
><tr id="gr_svn23_308"

><td id="308"><a href="#308">308</a></td></tr
><tr id="gr_svn23_309"

><td id="309"><a href="#309">309</a></td></tr
><tr id="gr_svn23_310"

><td id="310"><a href="#310">310</a></td></tr
><tr id="gr_svn23_311"

><td id="311"><a href="#311">311</a></td></tr
><tr id="gr_svn23_312"

><td id="312"><a href="#312">312</a></td></tr
><tr id="gr_svn23_313"

><td id="313"><a href="#313">313</a></td></tr
><tr id="gr_svn23_314"

><td id="314"><a href="#314">314</a></td></tr
><tr id="gr_svn23_315"

><td id="315"><a href="#315">315</a></td></tr
><tr id="gr_svn23_316"

><td id="316"><a href="#316">316</a></td></tr
><tr id="gr_svn23_317"

><td id="317"><a href="#317">317</a></td></tr
><tr id="gr_svn23_318"

><td id="318"><a href="#318">318</a></td></tr
><tr id="gr_svn23_319"

><td id="319"><a href="#319">319</a></td></tr
><tr id="gr_svn23_320"

><td id="320"><a href="#320">320</a></td></tr
><tr id="gr_svn23_321"

><td id="321"><a href="#321">321</a></td></tr
><tr id="gr_svn23_322"

><td id="322"><a href="#322">322</a></td></tr
><tr id="gr_svn23_323"

><td id="323"><a href="#323">323</a></td></tr
><tr id="gr_svn23_324"

><td id="324"><a href="#324">324</a></td></tr
><tr id="gr_svn23_325"

><td id="325"><a href="#325">325</a></td></tr
><tr id="gr_svn23_326"

><td id="326"><a href="#326">326</a></td></tr
><tr id="gr_svn23_327"

><td id="327"><a href="#327">327</a></td></tr
><tr id="gr_svn23_328"

><td id="328"><a href="#328">328</a></td></tr
><tr id="gr_svn23_329"

><td id="329"><a href="#329">329</a></td></tr
><tr id="gr_svn23_330"

><td id="330"><a href="#330">330</a></td></tr
><tr id="gr_svn23_331"

><td id="331"><a href="#331">331</a></td></tr
><tr id="gr_svn23_332"

><td id="332"><a href="#332">332</a></td></tr
><tr id="gr_svn23_333"

><td id="333"><a href="#333">333</a></td></tr
><tr id="gr_svn23_334"

><td id="334"><a href="#334">334</a></td></tr
><tr id="gr_svn23_335"

><td id="335"><a href="#335">335</a></td></tr
><tr id="gr_svn23_336"

><td id="336"><a href="#336">336</a></td></tr
><tr id="gr_svn23_337"

><td id="337"><a href="#337">337</a></td></tr
><tr id="gr_svn23_338"

><td id="338"><a href="#338">338</a></td></tr
><tr id="gr_svn23_339"

><td id="339"><a href="#339">339</a></td></tr
><tr id="gr_svn23_340"

><td id="340"><a href="#340">340</a></td></tr
><tr id="gr_svn23_341"

><td id="341"><a href="#341">341</a></td></tr
><tr id="gr_svn23_342"

><td id="342"><a href="#342">342</a></td></tr
><tr id="gr_svn23_343"

><td id="343"><a href="#343">343</a></td></tr
><tr id="gr_svn23_344"

><td id="344"><a href="#344">344</a></td></tr
><tr id="gr_svn23_345"

><td id="345"><a href="#345">345</a></td></tr
><tr id="gr_svn23_346"

><td id="346"><a href="#346">346</a></td></tr
><tr id="gr_svn23_347"

><td id="347"><a href="#347">347</a></td></tr
><tr id="gr_svn23_348"

><td id="348"><a href="#348">348</a></td></tr
><tr id="gr_svn23_349"

><td id="349"><a href="#349">349</a></td></tr
><tr id="gr_svn23_350"

><td id="350"><a href="#350">350</a></td></tr
><tr id="gr_svn23_351"

><td id="351"><a href="#351">351</a></td></tr
><tr id="gr_svn23_352"

><td id="352"><a href="#352">352</a></td></tr
><tr id="gr_svn23_353"

><td id="353"><a href="#353">353</a></td></tr
><tr id="gr_svn23_354"

><td id="354"><a href="#354">354</a></td></tr
><tr id="gr_svn23_355"

><td id="355"><a href="#355">355</a></td></tr
><tr id="gr_svn23_356"

><td id="356"><a href="#356">356</a></td></tr
><tr id="gr_svn23_357"

><td id="357"><a href="#357">357</a></td></tr
><tr id="gr_svn23_358"

><td id="358"><a href="#358">358</a></td></tr
><tr id="gr_svn23_359"

><td id="359"><a href="#359">359</a></td></tr
><tr id="gr_svn23_360"

><td id="360"><a href="#360">360</a></td></tr
><tr id="gr_svn23_361"

><td id="361"><a href="#361">361</a></td></tr
><tr id="gr_svn23_362"

><td id="362"><a href="#362">362</a></td></tr
><tr id="gr_svn23_363"

><td id="363"><a href="#363">363</a></td></tr
><tr id="gr_svn23_364"

><td id="364"><a href="#364">364</a></td></tr
><tr id="gr_svn23_365"

><td id="365"><a href="#365">365</a></td></tr
><tr id="gr_svn23_366"

><td id="366"><a href="#366">366</a></td></tr
><tr id="gr_svn23_367"

><td id="367"><a href="#367">367</a></td></tr
><tr id="gr_svn23_368"

><td id="368"><a href="#368">368</a></td></tr
><tr id="gr_svn23_369"

><td id="369"><a href="#369">369</a></td></tr
><tr id="gr_svn23_370"

><td id="370"><a href="#370">370</a></td></tr
><tr id="gr_svn23_371"

><td id="371"><a href="#371">371</a></td></tr
><tr id="gr_svn23_372"

><td id="372"><a href="#372">372</a></td></tr
><tr id="gr_svn23_373"

><td id="373"><a href="#373">373</a></td></tr
><tr id="gr_svn23_374"

><td id="374"><a href="#374">374</a></td></tr
><tr id="gr_svn23_375"

><td id="375"><a href="#375">375</a></td></tr
><tr id="gr_svn23_376"

><td id="376"><a href="#376">376</a></td></tr
><tr id="gr_svn23_377"

><td id="377"><a href="#377">377</a></td></tr
><tr id="gr_svn23_378"

><td id="378"><a href="#378">378</a></td></tr
><tr id="gr_svn23_379"

><td id="379"><a href="#379">379</a></td></tr
><tr id="gr_svn23_380"

><td id="380"><a href="#380">380</a></td></tr
><tr id="gr_svn23_381"

><td id="381"><a href="#381">381</a></td></tr
><tr id="gr_svn23_382"

><td id="382"><a href="#382">382</a></td></tr
><tr id="gr_svn23_383"

><td id="383"><a href="#383">383</a></td></tr
><tr id="gr_svn23_384"

><td id="384"><a href="#384">384</a></td></tr
><tr id="gr_svn23_385"

><td id="385"><a href="#385">385</a></td></tr
><tr id="gr_svn23_386"

><td id="386"><a href="#386">386</a></td></tr
><tr id="gr_svn23_387"

><td id="387"><a href="#387">387</a></td></tr
><tr id="gr_svn23_388"

><td id="388"><a href="#388">388</a></td></tr
><tr id="gr_svn23_389"

><td id="389"><a href="#389">389</a></td></tr
><tr id="gr_svn23_390"

><td id="390"><a href="#390">390</a></td></tr
><tr id="gr_svn23_391"

><td id="391"><a href="#391">391</a></td></tr
><tr id="gr_svn23_392"

><td id="392"><a href="#392">392</a></td></tr
><tr id="gr_svn23_393"

><td id="393"><a href="#393">393</a></td></tr
><tr id="gr_svn23_394"

><td id="394"><a href="#394">394</a></td></tr
><tr id="gr_svn23_395"

><td id="395"><a href="#395">395</a></td></tr
><tr id="gr_svn23_396"

><td id="396"><a href="#396">396</a></td></tr
><tr id="gr_svn23_397"

><td id="397"><a href="#397">397</a></td></tr
><tr id="gr_svn23_398"

><td id="398"><a href="#398">398</a></td></tr
><tr id="gr_svn23_399"

><td id="399"><a href="#399">399</a></td></tr
><tr id="gr_svn23_400"

><td id="400"><a href="#400">400</a></td></tr
><tr id="gr_svn23_401"

><td id="401"><a href="#401">401</a></td></tr
><tr id="gr_svn23_402"

><td id="402"><a href="#402">402</a></td></tr
><tr id="gr_svn23_403"

><td id="403"><a href="#403">403</a></td></tr
><tr id="gr_svn23_404"

><td id="404"><a href="#404">404</a></td></tr
><tr id="gr_svn23_405"

><td id="405"><a href="#405">405</a></td></tr
><tr id="gr_svn23_406"

><td id="406"><a href="#406">406</a></td></tr
><tr id="gr_svn23_407"

><td id="407"><a href="#407">407</a></td></tr
><tr id="gr_svn23_408"

><td id="408"><a href="#408">408</a></td></tr
><tr id="gr_svn23_409"

><td id="409"><a href="#409">409</a></td></tr
><tr id="gr_svn23_410"

><td id="410"><a href="#410">410</a></td></tr
><tr id="gr_svn23_411"

><td id="411"><a href="#411">411</a></td></tr
><tr id="gr_svn23_412"

><td id="412"><a href="#412">412</a></td></tr
><tr id="gr_svn23_413"

><td id="413"><a href="#413">413</a></td></tr
><tr id="gr_svn23_414"

><td id="414"><a href="#414">414</a></td></tr
><tr id="gr_svn23_415"

><td id="415"><a href="#415">415</a></td></tr
><tr id="gr_svn23_416"

><td id="416"><a href="#416">416</a></td></tr
><tr id="gr_svn23_417"

><td id="417"><a href="#417">417</a></td></tr
><tr id="gr_svn23_418"

><td id="418"><a href="#418">418</a></td></tr
><tr id="gr_svn23_419"

><td id="419"><a href="#419">419</a></td></tr
><tr id="gr_svn23_420"

><td id="420"><a href="#420">420</a></td></tr
><tr id="gr_svn23_421"

><td id="421"><a href="#421">421</a></td></tr
><tr id="gr_svn23_422"

><td id="422"><a href="#422">422</a></td></tr
><tr id="gr_svn23_423"

><td id="423"><a href="#423">423</a></td></tr
><tr id="gr_svn23_424"

><td id="424"><a href="#424">424</a></td></tr
><tr id="gr_svn23_425"

><td id="425"><a href="#425">425</a></td></tr
><tr id="gr_svn23_426"

><td id="426"><a href="#426">426</a></td></tr
><tr id="gr_svn23_427"

><td id="427"><a href="#427">427</a></td></tr
><tr id="gr_svn23_428"

><td id="428"><a href="#428">428</a></td></tr
><tr id="gr_svn23_429"

><td id="429"><a href="#429">429</a></td></tr
><tr id="gr_svn23_430"

><td id="430"><a href="#430">430</a></td></tr
><tr id="gr_svn23_431"

><td id="431"><a href="#431">431</a></td></tr
><tr id="gr_svn23_432"

><td id="432"><a href="#432">432</a></td></tr
><tr id="gr_svn23_433"

><td id="433"><a href="#433">433</a></td></tr
><tr id="gr_svn23_434"

><td id="434"><a href="#434">434</a></td></tr
><tr id="gr_svn23_435"

><td id="435"><a href="#435">435</a></td></tr
><tr id="gr_svn23_436"

><td id="436"><a href="#436">436</a></td></tr
><tr id="gr_svn23_437"

><td id="437"><a href="#437">437</a></td></tr
><tr id="gr_svn23_438"

><td id="438"><a href="#438">438</a></td></tr
><tr id="gr_svn23_439"

><td id="439"><a href="#439">439</a></td></tr
><tr id="gr_svn23_440"

><td id="440"><a href="#440">440</a></td></tr
><tr id="gr_svn23_441"

><td id="441"><a href="#441">441</a></td></tr
><tr id="gr_svn23_442"

><td id="442"><a href="#442">442</a></td></tr
><tr id="gr_svn23_443"

><td id="443"><a href="#443">443</a></td></tr
><tr id="gr_svn23_444"

><td id="444"><a href="#444">444</a></td></tr
><tr id="gr_svn23_445"

><td id="445"><a href="#445">445</a></td></tr
><tr id="gr_svn23_446"

><td id="446"><a href="#446">446</a></td></tr
><tr id="gr_svn23_447"

><td id="447"><a href="#447">447</a></td></tr
><tr id="gr_svn23_448"

><td id="448"><a href="#448">448</a></td></tr
><tr id="gr_svn23_449"

><td id="449"><a href="#449">449</a></td></tr
><tr id="gr_svn23_450"

><td id="450"><a href="#450">450</a></td></tr
><tr id="gr_svn23_451"

><td id="451"><a href="#451">451</a></td></tr
><tr id="gr_svn23_452"

><td id="452"><a href="#452">452</a></td></tr
><tr id="gr_svn23_453"

><td id="453"><a href="#453">453</a></td></tr
><tr id="gr_svn23_454"

><td id="454"><a href="#454">454</a></td></tr
><tr id="gr_svn23_455"

><td id="455"><a href="#455">455</a></td></tr
><tr id="gr_svn23_456"

><td id="456"><a href="#456">456</a></td></tr
><tr id="gr_svn23_457"

><td id="457"><a href="#457">457</a></td></tr
><tr id="gr_svn23_458"

><td id="458"><a href="#458">458</a></td></tr
><tr id="gr_svn23_459"

><td id="459"><a href="#459">459</a></td></tr
><tr id="gr_svn23_460"

><td id="460"><a href="#460">460</a></td></tr
><tr id="gr_svn23_461"

><td id="461"><a href="#461">461</a></td></tr
><tr id="gr_svn23_462"

><td id="462"><a href="#462">462</a></td></tr
><tr id="gr_svn23_463"

><td id="463"><a href="#463">463</a></td></tr
><tr id="gr_svn23_464"

><td id="464"><a href="#464">464</a></td></tr
><tr id="gr_svn23_465"

><td id="465"><a href="#465">465</a></td></tr
><tr id="gr_svn23_466"

><td id="466"><a href="#466">466</a></td></tr
><tr id="gr_svn23_467"

><td id="467"><a href="#467">467</a></td></tr
><tr id="gr_svn23_468"

><td id="468"><a href="#468">468</a></td></tr
><tr id="gr_svn23_469"

><td id="469"><a href="#469">469</a></td></tr
><tr id="gr_svn23_470"

><td id="470"><a href="#470">470</a></td></tr
><tr id="gr_svn23_471"

><td id="471"><a href="#471">471</a></td></tr
><tr id="gr_svn23_472"

><td id="472"><a href="#472">472</a></td></tr
><tr id="gr_svn23_473"

><td id="473"><a href="#473">473</a></td></tr
><tr id="gr_svn23_474"

><td id="474"><a href="#474">474</a></td></tr
><tr id="gr_svn23_475"

><td id="475"><a href="#475">475</a></td></tr
><tr id="gr_svn23_476"

><td id="476"><a href="#476">476</a></td></tr
><tr id="gr_svn23_477"

><td id="477"><a href="#477">477</a></td></tr
><tr id="gr_svn23_478"

><td id="478"><a href="#478">478</a></td></tr
><tr id="gr_svn23_479"

><td id="479"><a href="#479">479</a></td></tr
><tr id="gr_svn23_480"

><td id="480"><a href="#480">480</a></td></tr
><tr id="gr_svn23_481"

><td id="481"><a href="#481">481</a></td></tr
><tr id="gr_svn23_482"

><td id="482"><a href="#482">482</a></td></tr
><tr id="gr_svn23_483"

><td id="483"><a href="#483">483</a></td></tr
><tr id="gr_svn23_484"

><td id="484"><a href="#484">484</a></td></tr
><tr id="gr_svn23_485"

><td id="485"><a href="#485">485</a></td></tr
><tr id="gr_svn23_486"

><td id="486"><a href="#486">486</a></td></tr
><tr id="gr_svn23_487"

><td id="487"><a href="#487">487</a></td></tr
><tr id="gr_svn23_488"

><td id="488"><a href="#488">488</a></td></tr
><tr id="gr_svn23_489"

><td id="489"><a href="#489">489</a></td></tr
><tr id="gr_svn23_490"

><td id="490"><a href="#490">490</a></td></tr
><tr id="gr_svn23_491"

><td id="491"><a href="#491">491</a></td></tr
><tr id="gr_svn23_492"

><td id="492"><a href="#492">492</a></td></tr
><tr id="gr_svn23_493"

><td id="493"><a href="#493">493</a></td></tr
><tr id="gr_svn23_494"

><td id="494"><a href="#494">494</a></td></tr
><tr id="gr_svn23_495"

><td id="495"><a href="#495">495</a></td></tr
><tr id="gr_svn23_496"

><td id="496"><a href="#496">496</a></td></tr
><tr id="gr_svn23_497"

><td id="497"><a href="#497">497</a></td></tr
><tr id="gr_svn23_498"

><td id="498"><a href="#498">498</a></td></tr
><tr id="gr_svn23_499"

><td id="499"><a href="#499">499</a></td></tr
><tr id="gr_svn23_500"

><td id="500"><a href="#500">500</a></td></tr
><tr id="gr_svn23_501"

><td id="501"><a href="#501">501</a></td></tr
><tr id="gr_svn23_502"

><td id="502"><a href="#502">502</a></td></tr
><tr id="gr_svn23_503"

><td id="503"><a href="#503">503</a></td></tr
><tr id="gr_svn23_504"

><td id="504"><a href="#504">504</a></td></tr
><tr id="gr_svn23_505"

><td id="505"><a href="#505">505</a></td></tr
><tr id="gr_svn23_506"

><td id="506"><a href="#506">506</a></td></tr
><tr id="gr_svn23_507"

><td id="507"><a href="#507">507</a></td></tr
><tr id="gr_svn23_508"

><td id="508"><a href="#508">508</a></td></tr
><tr id="gr_svn23_509"

><td id="509"><a href="#509">509</a></td></tr
><tr id="gr_svn23_510"

><td id="510"><a href="#510">510</a></td></tr
><tr id="gr_svn23_511"

><td id="511"><a href="#511">511</a></td></tr
><tr id="gr_svn23_512"

><td id="512"><a href="#512">512</a></td></tr
><tr id="gr_svn23_513"

><td id="513"><a href="#513">513</a></td></tr
><tr id="gr_svn23_514"

><td id="514"><a href="#514">514</a></td></tr
><tr id="gr_svn23_515"

><td id="515"><a href="#515">515</a></td></tr
><tr id="gr_svn23_516"

><td id="516"><a href="#516">516</a></td></tr
><tr id="gr_svn23_517"

><td id="517"><a href="#517">517</a></td></tr
><tr id="gr_svn23_518"

><td id="518"><a href="#518">518</a></td></tr
><tr id="gr_svn23_519"

><td id="519"><a href="#519">519</a></td></tr
><tr id="gr_svn23_520"

><td id="520"><a href="#520">520</a></td></tr
><tr id="gr_svn23_521"

><td id="521"><a href="#521">521</a></td></tr
><tr id="gr_svn23_522"

><td id="522"><a href="#522">522</a></td></tr
><tr id="gr_svn23_523"

><td id="523"><a href="#523">523</a></td></tr
><tr id="gr_svn23_524"

><td id="524"><a href="#524">524</a></td></tr
><tr id="gr_svn23_525"

><td id="525"><a href="#525">525</a></td></tr
><tr id="gr_svn23_526"

><td id="526"><a href="#526">526</a></td></tr
><tr id="gr_svn23_527"

><td id="527"><a href="#527">527</a></td></tr
><tr id="gr_svn23_528"

><td id="528"><a href="#528">528</a></td></tr
><tr id="gr_svn23_529"

><td id="529"><a href="#529">529</a></td></tr
><tr id="gr_svn23_530"

><td id="530"><a href="#530">530</a></td></tr
><tr id="gr_svn23_531"

><td id="531"><a href="#531">531</a></td></tr
><tr id="gr_svn23_532"

><td id="532"><a href="#532">532</a></td></tr
><tr id="gr_svn23_533"

><td id="533"><a href="#533">533</a></td></tr
><tr id="gr_svn23_534"

><td id="534"><a href="#534">534</a></td></tr
><tr id="gr_svn23_535"

><td id="535"><a href="#535">535</a></td></tr
><tr id="gr_svn23_536"

><td id="536"><a href="#536">536</a></td></tr
><tr id="gr_svn23_537"

><td id="537"><a href="#537">537</a></td></tr
><tr id="gr_svn23_538"

><td id="538"><a href="#538">538</a></td></tr
><tr id="gr_svn23_539"

><td id="539"><a href="#539">539</a></td></tr
><tr id="gr_svn23_540"

><td id="540"><a href="#540">540</a></td></tr
><tr id="gr_svn23_541"

><td id="541"><a href="#541">541</a></td></tr
><tr id="gr_svn23_542"

><td id="542"><a href="#542">542</a></td></tr
><tr id="gr_svn23_543"

><td id="543"><a href="#543">543</a></td></tr
><tr id="gr_svn23_544"

><td id="544"><a href="#544">544</a></td></tr
><tr id="gr_svn23_545"

><td id="545"><a href="#545">545</a></td></tr
><tr id="gr_svn23_546"

><td id="546"><a href="#546">546</a></td></tr
><tr id="gr_svn23_547"

><td id="547"><a href="#547">547</a></td></tr
><tr id="gr_svn23_548"

><td id="548"><a href="#548">548</a></td></tr
><tr id="gr_svn23_549"

><td id="549"><a href="#549">549</a></td></tr
><tr id="gr_svn23_550"

><td id="550"><a href="#550">550</a></td></tr
><tr id="gr_svn23_551"

><td id="551"><a href="#551">551</a></td></tr
><tr id="gr_svn23_552"

><td id="552"><a href="#552">552</a></td></tr
><tr id="gr_svn23_553"

><td id="553"><a href="#553">553</a></td></tr
><tr id="gr_svn23_554"

><td id="554"><a href="#554">554</a></td></tr
><tr id="gr_svn23_555"

><td id="555"><a href="#555">555</a></td></tr
><tr id="gr_svn23_556"

><td id="556"><a href="#556">556</a></td></tr
><tr id="gr_svn23_557"

><td id="557"><a href="#557">557</a></td></tr
><tr id="gr_svn23_558"

><td id="558"><a href="#558">558</a></td></tr
><tr id="gr_svn23_559"

><td id="559"><a href="#559">559</a></td></tr
><tr id="gr_svn23_560"

><td id="560"><a href="#560">560</a></td></tr
><tr id="gr_svn23_561"

><td id="561"><a href="#561">561</a></td></tr
><tr id="gr_svn23_562"

><td id="562"><a href="#562">562</a></td></tr
><tr id="gr_svn23_563"

><td id="563"><a href="#563">563</a></td></tr
><tr id="gr_svn23_564"

><td id="564"><a href="#564">564</a></td></tr
><tr id="gr_svn23_565"

><td id="565"><a href="#565">565</a></td></tr
><tr id="gr_svn23_566"

><td id="566"><a href="#566">566</a></td></tr
><tr id="gr_svn23_567"

><td id="567"><a href="#567">567</a></td></tr
><tr id="gr_svn23_568"

><td id="568"><a href="#568">568</a></td></tr
><tr id="gr_svn23_569"

><td id="569"><a href="#569">569</a></td></tr
><tr id="gr_svn23_570"

><td id="570"><a href="#570">570</a></td></tr
><tr id="gr_svn23_571"

><td id="571"><a href="#571">571</a></td></tr
><tr id="gr_svn23_572"

><td id="572"><a href="#572">572</a></td></tr
><tr id="gr_svn23_573"

><td id="573"><a href="#573">573</a></td></tr
><tr id="gr_svn23_574"

><td id="574"><a href="#574">574</a></td></tr
><tr id="gr_svn23_575"

><td id="575"><a href="#575">575</a></td></tr
><tr id="gr_svn23_576"

><td id="576"><a href="#576">576</a></td></tr
><tr id="gr_svn23_577"

><td id="577"><a href="#577">577</a></td></tr
><tr id="gr_svn23_578"

><td id="578"><a href="#578">578</a></td></tr
><tr id="gr_svn23_579"

><td id="579"><a href="#579">579</a></td></tr
><tr id="gr_svn23_580"

><td id="580"><a href="#580">580</a></td></tr
><tr id="gr_svn23_581"

><td id="581"><a href="#581">581</a></td></tr
><tr id="gr_svn23_582"

><td id="582"><a href="#582">582</a></td></tr
><tr id="gr_svn23_583"

><td id="583"><a href="#583">583</a></td></tr
><tr id="gr_svn23_584"

><td id="584"><a href="#584">584</a></td></tr
><tr id="gr_svn23_585"

><td id="585"><a href="#585">585</a></td></tr
><tr id="gr_svn23_586"

><td id="586"><a href="#586">586</a></td></tr
><tr id="gr_svn23_587"

><td id="587"><a href="#587">587</a></td></tr
><tr id="gr_svn23_588"

><td id="588"><a href="#588">588</a></td></tr
><tr id="gr_svn23_589"

><td id="589"><a href="#589">589</a></td></tr
><tr id="gr_svn23_590"

><td id="590"><a href="#590">590</a></td></tr
><tr id="gr_svn23_591"

><td id="591"><a href="#591">591</a></td></tr
><tr id="gr_svn23_592"

><td id="592"><a href="#592">592</a></td></tr
><tr id="gr_svn23_593"

><td id="593"><a href="#593">593</a></td></tr
><tr id="gr_svn23_594"

><td id="594"><a href="#594">594</a></td></tr
><tr id="gr_svn23_595"

><td id="595"><a href="#595">595</a></td></tr
><tr id="gr_svn23_596"

><td id="596"><a href="#596">596</a></td></tr
><tr id="gr_svn23_597"

><td id="597"><a href="#597">597</a></td></tr
><tr id="gr_svn23_598"

><td id="598"><a href="#598">598</a></td></tr
><tr id="gr_svn23_599"

><td id="599"><a href="#599">599</a></td></tr
><tr id="gr_svn23_600"

><td id="600"><a href="#600">600</a></td></tr
><tr id="gr_svn23_601"

><td id="601"><a href="#601">601</a></td></tr
><tr id="gr_svn23_602"

><td id="602"><a href="#602">602</a></td></tr
><tr id="gr_svn23_603"

><td id="603"><a href="#603">603</a></td></tr
><tr id="gr_svn23_604"

><td id="604"><a href="#604">604</a></td></tr
><tr id="gr_svn23_605"

><td id="605"><a href="#605">605</a></td></tr
><tr id="gr_svn23_606"

><td id="606"><a href="#606">606</a></td></tr
><tr id="gr_svn23_607"

><td id="607"><a href="#607">607</a></td></tr
><tr id="gr_svn23_608"

><td id="608"><a href="#608">608</a></td></tr
><tr id="gr_svn23_609"

><td id="609"><a href="#609">609</a></td></tr
><tr id="gr_svn23_610"

><td id="610"><a href="#610">610</a></td></tr
><tr id="gr_svn23_611"

><td id="611"><a href="#611">611</a></td></tr
><tr id="gr_svn23_612"

><td id="612"><a href="#612">612</a></td></tr
><tr id="gr_svn23_613"

><td id="613"><a href="#613">613</a></td></tr
><tr id="gr_svn23_614"

><td id="614"><a href="#614">614</a></td></tr
><tr id="gr_svn23_615"

><td id="615"><a href="#615">615</a></td></tr
><tr id="gr_svn23_616"

><td id="616"><a href="#616">616</a></td></tr
><tr id="gr_svn23_617"

><td id="617"><a href="#617">617</a></td></tr
><tr id="gr_svn23_618"

><td id="618"><a href="#618">618</a></td></tr
><tr id="gr_svn23_619"

><td id="619"><a href="#619">619</a></td></tr
><tr id="gr_svn23_620"

><td id="620"><a href="#620">620</a></td></tr
><tr id="gr_svn23_621"

><td id="621"><a href="#621">621</a></td></tr
><tr id="gr_svn23_622"

><td id="622"><a href="#622">622</a></td></tr
><tr id="gr_svn23_623"

><td id="623"><a href="#623">623</a></td></tr
><tr id="gr_svn23_624"

><td id="624"><a href="#624">624</a></td></tr
><tr id="gr_svn23_625"

><td id="625"><a href="#625">625</a></td></tr
><tr id="gr_svn23_626"

><td id="626"><a href="#626">626</a></td></tr
><tr id="gr_svn23_627"

><td id="627"><a href="#627">627</a></td></tr
><tr id="gr_svn23_628"

><td id="628"><a href="#628">628</a></td></tr
><tr id="gr_svn23_629"

><td id="629"><a href="#629">629</a></td></tr
><tr id="gr_svn23_630"

><td id="630"><a href="#630">630</a></td></tr
><tr id="gr_svn23_631"

><td id="631"><a href="#631">631</a></td></tr
><tr id="gr_svn23_632"

><td id="632"><a href="#632">632</a></td></tr
><tr id="gr_svn23_633"

><td id="633"><a href="#633">633</a></td></tr
><tr id="gr_svn23_634"

><td id="634"><a href="#634">634</a></td></tr
><tr id="gr_svn23_635"

><td id="635"><a href="#635">635</a></td></tr
><tr id="gr_svn23_636"

><td id="636"><a href="#636">636</a></td></tr
><tr id="gr_svn23_637"

><td id="637"><a href="#637">637</a></td></tr
><tr id="gr_svn23_638"

><td id="638"><a href="#638">638</a></td></tr
><tr id="gr_svn23_639"

><td id="639"><a href="#639">639</a></td></tr
><tr id="gr_svn23_640"

><td id="640"><a href="#640">640</a></td></tr
><tr id="gr_svn23_641"

><td id="641"><a href="#641">641</a></td></tr
><tr id="gr_svn23_642"

><td id="642"><a href="#642">642</a></td></tr
><tr id="gr_svn23_643"

><td id="643"><a href="#643">643</a></td></tr
><tr id="gr_svn23_644"

><td id="644"><a href="#644">644</a></td></tr
><tr id="gr_svn23_645"

><td id="645"><a href="#645">645</a></td></tr
><tr id="gr_svn23_646"

><td id="646"><a href="#646">646</a></td></tr
><tr id="gr_svn23_647"

><td id="647"><a href="#647">647</a></td></tr
><tr id="gr_svn23_648"

><td id="648"><a href="#648">648</a></td></tr
><tr id="gr_svn23_649"

><td id="649"><a href="#649">649</a></td></tr
><tr id="gr_svn23_650"

><td id="650"><a href="#650">650</a></td></tr
><tr id="gr_svn23_651"

><td id="651"><a href="#651">651</a></td></tr
><tr id="gr_svn23_652"

><td id="652"><a href="#652">652</a></td></tr
><tr id="gr_svn23_653"

><td id="653"><a href="#653">653</a></td></tr
><tr id="gr_svn23_654"

><td id="654"><a href="#654">654</a></td></tr
><tr id="gr_svn23_655"

><td id="655"><a href="#655">655</a></td></tr
><tr id="gr_svn23_656"

><td id="656"><a href="#656">656</a></td></tr
><tr id="gr_svn23_657"

><td id="657"><a href="#657">657</a></td></tr
><tr id="gr_svn23_658"

><td id="658"><a href="#658">658</a></td></tr
><tr id="gr_svn23_659"

><td id="659"><a href="#659">659</a></td></tr
><tr id="gr_svn23_660"

><td id="660"><a href="#660">660</a></td></tr
><tr id="gr_svn23_661"

><td id="661"><a href="#661">661</a></td></tr
><tr id="gr_svn23_662"

><td id="662"><a href="#662">662</a></td></tr
><tr id="gr_svn23_663"

><td id="663"><a href="#663">663</a></td></tr
><tr id="gr_svn23_664"

><td id="664"><a href="#664">664</a></td></tr
><tr id="gr_svn23_665"

><td id="665"><a href="#665">665</a></td></tr
><tr id="gr_svn23_666"

><td id="666"><a href="#666">666</a></td></tr
><tr id="gr_svn23_667"

><td id="667"><a href="#667">667</a></td></tr
><tr id="gr_svn23_668"

><td id="668"><a href="#668">668</a></td></tr
><tr id="gr_svn23_669"

><td id="669"><a href="#669">669</a></td></tr
><tr id="gr_svn23_670"

><td id="670"><a href="#670">670</a></td></tr
><tr id="gr_svn23_671"

><td id="671"><a href="#671">671</a></td></tr
><tr id="gr_svn23_672"

><td id="672"><a href="#672">672</a></td></tr
><tr id="gr_svn23_673"

><td id="673"><a href="#673">673</a></td></tr
><tr id="gr_svn23_674"

><td id="674"><a href="#674">674</a></td></tr
><tr id="gr_svn23_675"

><td id="675"><a href="#675">675</a></td></tr
><tr id="gr_svn23_676"

><td id="676"><a href="#676">676</a></td></tr
><tr id="gr_svn23_677"

><td id="677"><a href="#677">677</a></td></tr
></table></pre>
<pre><table width="100%"><tr class="nocursor"><td></td></tr></table></pre>
</td>
<td id="lines">
<pre><table width="100%"><tr class="cursor_stop cursor_hidden"><td></td></tr></table></pre>
<pre ><table id="src_table_0"><tr
id=sl_svn23_1

><td class="source">;-----------------------------------------------------------------------------;<br></td></tr
><tr
id=sl_svn23_2

><td class="source">; Fixed-point FFT routines for megaAVRs                        (C)ChaN, 2005<br></td></tr
><tr
id=sl_svn23_3

><td class="source">;-----------------------------------------------------------------------------;<br></td></tr
><tr
id=sl_svn23_4

><td class="source">;<br></td></tr
><tr
id=sl_svn23_5

><td class="source">; void fft_input (const int16_t *array_src, complex_t *array_bfly);<br></td></tr
><tr
id=sl_svn23_6

><td class="source">; void fft_execute (complex_t *array_bfly);<br></td></tr
><tr
id=sl_svn23_7

><td class="source">; void fft_output (complex_t *array_bfly, uint16_t *array_dst);<br></td></tr
><tr
id=sl_svn23_8

><td class="source">;<br></td></tr
><tr
id=sl_svn23_9

><td class="source">;  &lt;array_src&gt;: Wave form to be processed.<br></td></tr
><tr
id=sl_svn23_10

><td class="source">;  &lt;array_bfly&gt;: Complex array for butterfly operations.<br></td></tr
><tr
id=sl_svn23_11

><td class="source">;  &lt;array_dst&gt;: Spectrum output buffer.<br></td></tr
><tr
id=sl_svn23_12

><td class="source">;<br></td></tr
><tr
id=sl_svn23_13

><td class="source">; These functions must be called in sequence to do a DFT in FFT algorithm.<br></td></tr
><tr
id=sl_svn23_14

><td class="source">; fft_input() fills the complex array with a wave form to prepare butterfly<br></td></tr
><tr
id=sl_svn23_15

><td class="source">; operations. A hamming window is applied at the same time.<br></td></tr
><tr
id=sl_svn23_16

><td class="source">; fft_execute() executes the butterfly operations.<br></td></tr
><tr
id=sl_svn23_17

><td class="source">; fft_output() re-orders the results, converts the complex spectrum into<br></td></tr
><tr
id=sl_svn23_18

><td class="source">; scalar spectrum and output it in linear scale.<br></td></tr
><tr
id=sl_svn23_19

><td class="source">;<br></td></tr
><tr
id=sl_svn23_20

><td class="source">; The number of points FFT_N is defined in &quot;ffft.h&quot; and the value can be<br></td></tr
><tr
id=sl_svn23_21

><td class="source">; power of 2 in range of 64 - 1024.<br></td></tr
><tr
id=sl_svn23_22

><td class="source">;<br></td></tr
><tr
id=sl_svn23_23

><td class="source">;----------------------------------------------------------------------------;<br></td></tr
><tr
id=sl_svn23_24

><td class="source">; 16bit fixed-point FFT performance with MegaAVRs<br></td></tr
><tr
id=sl_svn23_25

><td class="source">; (Running at 16MHz/internal SRAM)<br></td></tr
><tr
id=sl_svn23_26

><td class="source">;<br></td></tr
><tr
id=sl_svn23_27

><td class="source">;  Points:   Input, Execute,  Output,    Total:  Throughput<br></td></tr
><tr
id=sl_svn23_28

><td class="source">;   64pts:   .17ms,   2.0ms,   1.2ms,    3.4ms:   19.0kpps<br></td></tr
><tr
id=sl_svn23_29

><td class="source">;  128pts:   .33ms,   4.6ms,   2.4ms,    7.3ms:   17.5kpps<br></td></tr
><tr
id=sl_svn23_30

><td class="source">;  256pts:   .66ms,  10.4ms,   4.9ms,   15.9ms:   16.1kpps<br></td></tr
><tr
id=sl_svn23_31

><td class="source">;  512pts:   1.3ms,  23.2ms,   9.7ms,   34.2ms:   14.9kpps<br></td></tr
><tr
id=sl_svn23_32

><td class="source">; 1024pts:   2.7ms,  51.7ms,  19.4ms,   73.7ms:   13.9kpps<br></td></tr
><tr
id=sl_svn23_33

><td class="source">;----------------------------------------------------------------------------;<br></td></tr
><tr
id=sl_svn23_34

><td class="source"><br></td></tr
><tr
id=sl_svn23_35

><td class="source"><br></td></tr
><tr
id=sl_svn23_36

><td class="source">.nolist<br></td></tr
><tr
id=sl_svn23_37

><td class="source">#define FFFT_ASM<br></td></tr
><tr
id=sl_svn23_38

><td class="source">#include &quot;ffft.h&quot;<br></td></tr
><tr
id=sl_svn23_39

><td class="source">.list<br></td></tr
><tr
id=sl_svn23_40

><td class="source"><br></td></tr
><tr
id=sl_svn23_41

><td class="source">#if FFT_N == 1024<br></td></tr
><tr
id=sl_svn23_42

><td class="source">#define FFT_B 10<br></td></tr
><tr
id=sl_svn23_43

><td class="source">#elif FFT_N == 512<br></td></tr
><tr
id=sl_svn23_44

><td class="source">#define FFT_B 9<br></td></tr
><tr
id=sl_svn23_45

><td class="source">#elif FFT_N == 256<br></td></tr
><tr
id=sl_svn23_46

><td class="source">#define FFT_B 8<br></td></tr
><tr
id=sl_svn23_47

><td class="source">#elif FFT_N == 128<br></td></tr
><tr
id=sl_svn23_48

><td class="source">#define FFT_B 7<br></td></tr
><tr
id=sl_svn23_49

><td class="source">#elif FFT_N == 64<br></td></tr
><tr
id=sl_svn23_50

><td class="source">#define FFT_B 6<br></td></tr
><tr
id=sl_svn23_51

><td class="source">#else<br></td></tr
><tr
id=sl_svn23_52

><td class="source">#error Wrong setting of FFT_N.<br></td></tr
><tr
id=sl_svn23_53

><td class="source">#endif<br></td></tr
><tr
id=sl_svn23_54

><td class="source"><br></td></tr
><tr
id=sl_svn23_55

><td class="source"><br></td></tr
><tr
id=sl_svn23_56

><td class="source">;----------------------------------------------------------------------------;<br></td></tr
><tr
id=sl_svn23_57

><td class="source">; Constant Tables<br></td></tr
><tr
id=sl_svn23_58

><td class="source"><br></td></tr
><tr
id=sl_svn23_59

><td class="source">.global tbl_window<br></td></tr
><tr
id=sl_svn23_60

><td class="source">tbl_window:	; tbl_window[] = ... (This is a Hamming window)<br></td></tr
><tr
id=sl_svn23_61

><td class="source">#if FFT_N == 1024<br></td></tr
><tr
id=sl_svn23_62

><td class="source">	.dc.w 2621, 2621, 2622, 2623, 2625, 2628, 2631, 2635, 2639, 2644, 2649, 2655, 2662, 2669, 2676, 2685<br></td></tr
><tr
id=sl_svn23_63

><td class="source">	.dc.w 2693, 2703, 2713, 2723, 2734, 2746, 2758, 2771, 2784, 2798, 2812, 2827, 2843, 2859, 2876, 2893<br></td></tr
><tr
id=sl_svn23_64

><td class="source">	.dc.w 2910, 2929, 2948, 2967, 2987, 3008, 3029, 3050, 3073, 3095, 3119, 3142, 3167, 3192, 3217, 3243<br></td></tr
><tr
id=sl_svn23_65

><td class="source">	.dc.w 3270, 3297, 3325, 3353, 3382, 3411, 3441, 3471, 3502, 3533, 3565, 3598, 3631, 3664, 3698, 3733<br></td></tr
><tr
id=sl_svn23_66

><td class="source">	.dc.w 3768, 3804, 3840, 3877, 3914, 3952, 3990, 4029, 4068, 4108, 4148, 4189, 4230, 4272, 4314, 4357<br></td></tr
><tr
id=sl_svn23_67

><td class="source">	.dc.w 4401, 4444, 4489, 4534, 4579, 4625, 4671, 4718, 4765, 4813, 4861, 4910, 4959, 5009, 5059, 5110<br></td></tr
><tr
id=sl_svn23_68

><td class="source">	.dc.w 5161, 5213, 5265, 5317, 5370, 5424, 5478, 5532, 5587, 5642, 5698, 5754, 5811, 5868, 5926, 5984<br></td></tr
><tr
id=sl_svn23_69

><td class="source">	.dc.w 6042, 6101, 6160, 6220, 6280, 6341, 6402, 6464, 6525, 6588, 6651, 6714, 6777, 6841, 6906, 6970<br></td></tr
><tr
id=sl_svn23_70

><td class="source">	.dc.w 7036, 7101, 7167, 7234, 7300, 7368, 7435, 7503, 7571, 7640, 7709, 7779, 7849, 7919, 7989, 8060<br></td></tr
><tr
id=sl_svn23_71

><td class="source">	.dc.w 8132, 8203, 8275, 8348, 8420, 8493, 8567, 8641, 8715, 8789, 8864, 8939, 9015, 9090, 9166, 9243<br></td></tr
><tr
id=sl_svn23_72

><td class="source">	.dc.w 9320, 9397, 9474, 9552, 9630, 9708, 9787, 9866, 9945, 10024, 10104, 10184, 10264, 10345, 10426, 10507<br></td></tr
><tr
id=sl_svn23_73

><td class="source">	.dc.w 10588, 10670, 10752, 10834, 10917, 10999, 11082, 11166, 11249, 11333, 11417, 11501, 11586, 11670, 11755, 11840<br></td></tr
><tr
id=sl_svn23_74

><td class="source">	.dc.w 11926, 12011, 12097, 12183, 12269, 12355, 12442, 12529, 12616, 12703, 12790, 12878, 12966, 13054, 13142, 13230<br></td></tr
><tr
id=sl_svn23_75

><td class="source">	.dc.w 13318, 13407, 13496, 13584, 13674, 13763, 13852, 13942, 14031, 14121, 14211, 14301, 14391, 14481, 14572, 14662<br></td></tr
><tr
id=sl_svn23_76

><td class="source">	.dc.w 14753, 14844, 14935, 15026, 15117, 15208, 15299, 15391, 15482, 15574, 15665, 15757, 15849, 15940, 16032, 16124<br></td></tr
><tr
id=sl_svn23_77

><td class="source">	.dc.w 16216, 16308, 16400, 16493, 16585, 16677, 16769, 16862, 16954, 17046, 17139, 17231, 17324, 17416, 17509, 17601<br></td></tr
><tr
id=sl_svn23_78

><td class="source">	.dc.w 17694, 17786, 17879, 17971, 18064, 18156, 18248, 18341, 18433, 18526, 18618, 18710, 18802, 18895, 18987, 19079<br></td></tr
><tr
id=sl_svn23_79

><td class="source">	.dc.w 19171, 19263, 19355, 19447, 19539, 19630, 19722, 19814, 19905, 19997, 20088, 20179, 20271, 20362, 20453, 20543<br></td></tr
><tr
id=sl_svn23_80

><td class="source">	.dc.w 20634, 20725, 20815, 20906, 20996, 21086, 21176, 21266, 21356, 21446, 21535, 21625, 21714, 21803, 21892, 21980<br></td></tr
><tr
id=sl_svn23_81

><td class="source">	.dc.w 22069, 22157, 22246, 22334, 22422, 22509, 22597, 22684, 22772, 22859, 22945, 23032, 23118, 23204, 23290, 23376<br></td></tr
><tr
id=sl_svn23_82

><td class="source">	.dc.w 23462, 23547, 23632, 23717, 23802, 23886, 23970, 24054, 24138, 24222, 24305, 24388, 24471, 24553, 24635, 24717<br></td></tr
><tr
id=sl_svn23_83

><td class="source">	.dc.w 24799, 24880, 24962, 25042, 25123, 25203, 25283, 25363, 25443, 25522, 25601, 25679, 25758, 25836, 25913, 25991<br></td></tr
><tr
id=sl_svn23_84

><td class="source">	.dc.w 26068, 26144, 26221, 26297, 26373, 26448, 26523, 26598, 26673, 26747, 26820, 26894, 26967, 27040, 27112, 27184<br></td></tr
><tr
id=sl_svn23_85

><td class="source">	.dc.w 27256, 27327, 27398, 27469, 27539, 27609, 27678, 27747, 27816, 27884, 27952, 28020, 28087, 28154, 28220, 28286<br></td></tr
><tr
id=sl_svn23_86

><td class="source">	.dc.w 28352, 28417, 28482, 28546, 28610, 28674, 28737, 28800, 28862, 28924, 28985, 29046, 29107, 29167, 29227, 29286<br></td></tr
><tr
id=sl_svn23_87

><td class="source">	.dc.w 29345, 29404, 29462, 29519, 29576, 29633, 29689, 29745, 29800, 29855, 29910, 29963, 30017, 30070, 30123, 30175<br></td></tr
><tr
id=sl_svn23_88

><td class="source">	.dc.w 30226, 30277, 30328, 30378, 30428, 30477, 30526, 30574, 30622, 30669, 30716, 30762, 30808, 30854, 30899, 30943<br></td></tr
><tr
id=sl_svn23_89

><td class="source">	.dc.w 30987, 31030, 31073, 31115, 31157, 31198, 31239, 31280, 31319, 31359, 31397, 31436, 31473, 31511, 31547, 31583<br></td></tr
><tr
id=sl_svn23_90

><td class="source">	.dc.w 31619, 31654, 31689, 31723, 31756, 31790, 31822, 31854, 31885, 31916, 31947, 31976, 32006, 32034, 32063, 32090<br></td></tr
><tr
id=sl_svn23_91

><td class="source">	.dc.w 32117, 32144, 32170, 32196, 32220, 32245, 32269, 32292, 32315, 32337, 32359, 32380, 32400, 32420, 32440, 32459<br></td></tr
><tr
id=sl_svn23_92

><td class="source">	.dc.w 32477, 32495, 32512, 32528, 32545, 32560, 32575, 32590, 32603, 32617, 32629, 32642, 32653, 32664, 32675, 32685<br></td></tr
><tr
id=sl_svn23_93

><td class="source">	.dc.w 32694, 32703, 32711, 32719, 32726, 32732, 32738, 32744, 32748, 32753, 32756, 32759, 32762, 32764, 32765, 32766<br></td></tr
><tr
id=sl_svn23_94

><td class="source">	.dc.w 32766, 32766, 32765, 32764, 32762, 32759, 32756, 32753, 32748, 32744, 32738, 32732, 32726, 32719, 32711, 32703<br></td></tr
><tr
id=sl_svn23_95

><td class="source">	.dc.w 32694, 32685, 32675, 32664, 32653, 32642, 32629, 32617, 32603, 32590, 32575, 32560, 32545, 32529, 32512, 32495<br></td></tr
><tr
id=sl_svn23_96

><td class="source">	.dc.w 32477, 32459, 32440, 32420, 32400, 32380, 32359, 32337, 32315, 32292, 32269, 32245, 32221, 32196, 32170, 32144<br></td></tr
><tr
id=sl_svn23_97

><td class="source">	.dc.w 32117, 32090, 32063, 32035, 32006, 31976, 31947, 31916, 31885, 31854, 31822, 31790, 31757, 31723, 31689, 31654<br></td></tr
><tr
id=sl_svn23_98

><td class="source">	.dc.w 31619, 31584, 31547, 31511, 31473, 31436, 31397, 31359, 31319, 31280, 31239, 31198, 31157, 31115, 31073, 31030<br></td></tr
><tr
id=sl_svn23_99

><td class="source">	.dc.w 30987, 30943, 30899, 30854, 30808, 30763, 30716, 30669, 30622, 30574, 30526, 30477, 30428, 30378, 30328, 30277<br></td></tr
><tr
id=sl_svn23_100

><td class="source">	.dc.w 30226, 30175, 30123, 30070, 30017, 29964, 29910, 29855, 29800, 29745, 29689, 29633, 29576, 29519, 29462, 29404<br></td></tr
><tr
id=sl_svn23_101

><td class="source">	.dc.w 29345, 29286, 29227, 29167, 29107, 29046, 28985, 28924, 28862, 28800, 28737, 28674, 28610, 28546, 28482, 28417<br></td></tr
><tr
id=sl_svn23_102

><td class="source">	.dc.w 28352, 28286, 28220, 28154, 28087, 28020, 27952, 27884, 27816, 27747, 27678, 27609, 27539, 27469, 27398, 27327<br></td></tr
><tr
id=sl_svn23_103

><td class="source">	.dc.w 27256, 27184, 27112, 27040, 26967, 26894, 26820, 26747, 26673, 26598, 26523, 26448, 26373, 26297, 26221, 26144<br></td></tr
><tr
id=sl_svn23_104

><td class="source">	.dc.w 26068, 25991, 25913, 25836, 25758, 25679, 25601, 25522, 25443, 25363, 25283, 25203, 25123, 25042, 24962, 24880<br></td></tr
><tr
id=sl_svn23_105

><td class="source">	.dc.w 24799, 24717, 24635, 24553, 24471, 24388, 24305, 24222, 24138, 24054, 23970, 23886, 23802, 23717, 23632, 23547<br></td></tr
><tr
id=sl_svn23_106

><td class="source">	.dc.w 23462, 23376, 23291, 23205, 23118, 23032, 22945, 22859, 22772, 22684, 22597, 22510, 22422, 22334, 22246, 22158<br></td></tr
><tr
id=sl_svn23_107

><td class="source">	.dc.w 22069, 21981, 21892, 21803, 21714, 21625, 21535, 21446, 21356, 21266, 21176, 21086, 20996, 20906, 20815, 20725<br></td></tr
><tr
id=sl_svn23_108

><td class="source">	.dc.w 20634, 20544, 20453, 20362, 20271, 20179, 20088, 19997, 19905, 19814, 19722, 19631, 19539, 19447, 19355, 19263<br></td></tr
><tr
id=sl_svn23_109

><td class="source">	.dc.w 19171, 19079, 18987, 18895, 18803, 18710, 18618, 18526, 18433, 18341, 18249, 18156, 18064, 17971, 17879, 17786<br></td></tr
><tr
id=sl_svn23_110

><td class="source">	.dc.w 17694, 17601, 17509, 17416, 17324, 17231, 17139, 17047, 16954, 16862, 16769, 16677, 16585, 16493, 16401, 16308<br></td></tr
><tr
id=sl_svn23_111

><td class="source">	.dc.w 16216, 16124, 16032, 15940, 15849, 15757, 15665, 15574, 15482, 15391, 15299, 15208, 15117, 15026, 14935, 14844<br></td></tr
><tr
id=sl_svn23_112

><td class="source">	.dc.w 14753, 14663, 14572, 14482, 14391, 14301, 14211, 14121, 14031, 13942, 13852, 13763, 13674, 13585, 13496, 13407<br></td></tr
><tr
id=sl_svn23_113

><td class="source">	.dc.w 13318, 13230, 13142, 13054, 12966, 12878, 12790, 12703, 12616, 12529, 12442, 12355, 12269, 12183, 12097, 12011<br></td></tr
><tr
id=sl_svn23_114

><td class="source">	.dc.w 11926, 11840, 11755, 11670, 11586, 11501, 11417, 11333, 11249, 11166, 11083, 11000, 10917, 10834, 10752, 10670<br></td></tr
><tr
id=sl_svn23_115

><td class="source">	.dc.w 10588, 10507, 10426, 10345, 10264, 10184, 10104, 10024, 9945, 9866, 9787, 9708, 9630, 9552, 9474, 9397<br></td></tr
><tr
id=sl_svn23_116

><td class="source">	.dc.w 9320, 9243, 9167, 9090, 9015, 8939, 8864, 8789, 8715, 8641, 8567, 8494, 8420, 8348, 8275, 8203<br></td></tr
><tr
id=sl_svn23_117

><td class="source">	.dc.w 8132, 8060, 7989, 7919, 7849, 7779, 7709, 7640, 7571, 7503, 7435, 7368, 7300, 7234, 7167, 7101<br></td></tr
><tr
id=sl_svn23_118

><td class="source">	.dc.w 7036, 6970, 6906, 6841, 6777, 6714, 6651, 6588, 6526, 6464, 6402, 6341, 6280, 6220, 6160, 6101<br></td></tr
><tr
id=sl_svn23_119

><td class="source">	.dc.w 6042, 5984, 5926, 5868, 5811, 5754, 5698, 5642, 5587, 5532, 5478, 5424, 5370, 5317, 5265, 5213<br></td></tr
><tr
id=sl_svn23_120

><td class="source">	.dc.w 5161, 5110, 5059, 5009, 4959, 4910, 4861, 4813, 4765, 4718, 4671, 4625, 4579, 4534, 4489, 4445<br></td></tr
><tr
id=sl_svn23_121

><td class="source">	.dc.w 4401, 4357, 4314, 4272, 4230, 4189, 4148, 4108, 4068, 4029, 3990, 3952, 3914, 3877, 3840, 3804<br></td></tr
><tr
id=sl_svn23_122

><td class="source">	.dc.w 3768, 3733, 3699, 3664, 3631, 3598, 3565, 3533, 3502, 3471, 3441, 3411, 3382, 3353, 3325, 3297<br></td></tr
><tr
id=sl_svn23_123

><td class="source">	.dc.w 3270, 3243, 3217, 3192, 3167, 3142, 3119, 3095, 3073, 3050, 3029, 3008, 2987, 2967, 2948, 2929<br></td></tr
><tr
id=sl_svn23_124

><td class="source">	.dc.w 2910, 2893, 2876, 2859, 2843, 2827, 2812, 2798, 2784, 2771, 2758, 2746, 2734, 2723, 2713, 2703<br></td></tr
><tr
id=sl_svn23_125

><td class="source">	.dc.w 2693, 2685, 2676, 2669, 2662, 2655, 2649, 2644, 2639, 2635, 2631, 2628, 2625, 2623, 2622, 2621<br></td></tr
><tr
id=sl_svn23_126

><td class="source"><br></td></tr
><tr
id=sl_svn23_127

><td class="source">#elif FFT_N == 512<br></td></tr
><tr
id=sl_svn23_128

><td class="source">	.dc.w	2621, 2622, 2625, 2631, 2639, 2649, 2662, 2676, 2693, 2713, 2734, 2758, 2784, 2812, 2843, 2876<br></td></tr
><tr
id=sl_svn23_129

><td class="source">	.dc.w	2910, 2948, 2987, 3029, 3073, 3119, 3167, 3217, 3270, 3325, 3382, 3441, 3502, 3565, 3631, 3698<br></td></tr
><tr
id=sl_svn23_130

><td class="source">	.dc.w	3768, 3840, 3914, 3990, 4068, 4148, 4230, 4314, 4401, 4489, 4579, 4671, 4765, 4861, 4959, 5059<br></td></tr
><tr
id=sl_svn23_131

><td class="source">	.dc.w	5161, 5265, 5370, 5478, 5587, 5698, 5811, 5926, 6042, 6160, 6280, 6402, 6525, 6651, 6777, 6906<br></td></tr
><tr
id=sl_svn23_132

><td class="source">	.dc.w	7036, 7167, 7300, 7435, 7571, 7709, 7849, 7989, 8132, 8275, 8420, 8567, 8715, 8864, 9015, 9166<br></td></tr
><tr
id=sl_svn23_133

><td class="source">	.dc.w	9320, 9474, 9630, 9787, 9945, 10104, 10264, 10426, 10588, 10752, 10917, 11082, 11249, 11417, 11586, 11755<br></td></tr
><tr
id=sl_svn23_134

><td class="source">	.dc.w	11926, 12097, 12269, 12442, 12616, 12790, 12966, 13142, 13318, 13496, 13674, 13852, 14031, 14211, 14391, 14572<br></td></tr
><tr
id=sl_svn23_135

><td class="source">	.dc.w	14753, 14935, 15117, 15299, 15482, 15665, 15849, 16032, 16216, 16400, 16585, 16769, 16954, 17139, 17324, 17509<br></td></tr
><tr
id=sl_svn23_136

><td class="source">	.dc.w	17694, 17879, 18064, 18248, 18433, 18618, 18802, 18987, 19171, 19355, 19539, 19722, 19905, 20088, 20271, 20453<br></td></tr
><tr
id=sl_svn23_137

><td class="source">	.dc.w	20634, 20815, 20996, 21176, 21356, 21535, 21714, 21892, 22069, 22246, 22422, 22597, 22772, 22945, 23118, 23290<br></td></tr
><tr
id=sl_svn23_138

><td class="source">	.dc.w	23462, 23632, 23802, 23970, 24138, 24305, 24471, 24635, 24799, 24962, 25123, 25283, 25443, 25601, 25758, 25913<br></td></tr
><tr
id=sl_svn23_139

><td class="source">	.dc.w	26068, 26221, 26373, 26523, 26673, 26820, 26967, 27112, 27256, 27398, 27539, 27678, 27816, 27952, 28087, 28220<br></td></tr
><tr
id=sl_svn23_140

><td class="source">	.dc.w	28352, 28482, 28610, 28737, 28862, 28985, 29107, 29227, 29345, 29462, 29576, 29689, 29800, 29910, 30017, 30123<br></td></tr
><tr
id=sl_svn23_141

><td class="source">	.dc.w	30226, 30328, 30428, 30526, 30622, 30716, 30808, 30899, 30987, 31073, 31157, 31239, 31319, 31397, 31473, 31547<br></td></tr
><tr
id=sl_svn23_142

><td class="source">	.dc.w	31619, 31689, 31756, 31822, 31885, 31947, 32006, 32063, 32117, 32170, 32220, 32269, 32315, 32359, 32400, 32440<br></td></tr
><tr
id=sl_svn23_143

><td class="source">	.dc.w	32477, 32512, 32545, 32575, 32603, 32629, 32653, 32675, 32694, 32711, 32726, 32738, 32748, 32756, 32762, 32765<br></td></tr
><tr
id=sl_svn23_144

><td class="source">	.dc.w	32766, 32765, 32762, 32756, 32748, 32738, 32726, 32711, 32694, 32675, 32653, 32629, 32603, 32575, 32545, 32512<br></td></tr
><tr
id=sl_svn23_145

><td class="source">	.dc.w	32477, 32440, 32400, 32359, 32315, 32269, 32221, 32170, 32117, 32063, 32006, 31947, 31885, 31822, 31757, 31689<br></td></tr
><tr
id=sl_svn23_146

><td class="source">	.dc.w	31619, 31547, 31473, 31397, 31319, 31239, 31157, 31073, 30987, 30899, 30808, 30716, 30622, 30526, 30428, 30328<br></td></tr
><tr
id=sl_svn23_147

><td class="source">	.dc.w	30226, 30123, 30017, 29910, 29800, 29689, 29576, 29462, 29345, 29227, 29107, 28985, 28862, 28737, 28610, 28482<br></td></tr
><tr
id=sl_svn23_148

><td class="source">	.dc.w	28352, 28220, 28087, 27952, 27816, 27678, 27539, 27398, 27256, 27112, 26967, 26820, 26673, 26523, 26373, 26221<br></td></tr
><tr
id=sl_svn23_149

><td class="source">	.dc.w	26068, 25913, 25758, 25601, 25443, 25283, 25123, 24962, 24799, 24635, 24471, 24305, 24138, 23970, 23802, 23632<br></td></tr
><tr
id=sl_svn23_150

><td class="source">	.dc.w	23462, 23291, 23118, 22945, 22772, 22597, 22422, 22246, 22069, 21892, 21714, 21535, 21356, 21176, 20996, 20815<br></td></tr
><tr
id=sl_svn23_151

><td class="source">	.dc.w	20634, 20453, 20271, 20088, 19905, 19722, 19539, 19355, 19171, 18987, 18803, 18618, 18433, 18249, 18064, 17879<br></td></tr
><tr
id=sl_svn23_152

><td class="source">	.dc.w	17694, 17509, 17324, 17139, 16954, 16769, 16585, 16401, 16216, 16032, 15849, 15665, 15482, 15299, 15117, 14935<br></td></tr
><tr
id=sl_svn23_153

><td class="source">	.dc.w	14753, 14572, 14391, 14211, 14031, 13852, 13674, 13496, 13318, 13142, 12966, 12790, 12616, 12442, 12269, 12097<br></td></tr
><tr
id=sl_svn23_154

><td class="source">	.dc.w	11926, 11755, 11586, 11417, 11249, 11083, 10917, 10752, 10588, 10426, 10264, 10104, 9945, 9787, 9630, 9474<br></td></tr
><tr
id=sl_svn23_155

><td class="source">	.dc.w	9320, 9167, 9015, 8864, 8715, 8567, 8420, 8275, 8132, 7989, 7849, 7709, 7571, 7435, 7300, 7167<br></td></tr
><tr
id=sl_svn23_156

><td class="source">	.dc.w	7036, 6906, 6777, 6651, 6526, 6402, 6280, 6160, 6042, 5926, 5811, 5698, 5587, 5478, 5370, 5265<br></td></tr
><tr
id=sl_svn23_157

><td class="source">	.dc.w	5161, 5059, 4959, 4861, 4765, 4671, 4579, 4489, 4401, 4314, 4230, 4148, 4068, 3990, 3914, 3840<br></td></tr
><tr
id=sl_svn23_158

><td class="source">	.dc.w	3768, 3699, 3631, 3565, 3502, 3441, 3382, 3325, 3270, 3217, 3167, 3119, 3073, 3029, 2987, 2948<br></td></tr
><tr
id=sl_svn23_159

><td class="source">	.dc.w	2910, 2876, 2843, 2812, 2784, 2758, 2734, 2713, 2693, 2676, 2662, 2649, 2639, 2631, 2625, 2622<br></td></tr
><tr
id=sl_svn23_160

><td class="source"><br></td></tr
><tr
id=sl_svn23_161

><td class="source">#elif FFT_N == 256<br></td></tr
><tr
id=sl_svn23_162

><td class="source">	.dc.w	2621, 2625, 2639, 2662, 2693, 2734, 2784, 2843, 2910, 2987, 3073, 3167, 3270, 3382, 3502, 3631<br></td></tr
><tr
id=sl_svn23_163

><td class="source">	.dc.w	3768, 3914, 4068, 4230, 4401, 4579, 4765, 4959, 5161, 5370, 5587, 5811, 6042, 6280, 6525, 6777<br></td></tr
><tr
id=sl_svn23_164

><td class="source">	.dc.w	7036, 7300, 7571, 7849, 8132, 8420, 8715, 9015, 9320, 9630, 9945, 10264, 10588, 10917, 11249, 11586<br></td></tr
><tr
id=sl_svn23_165

><td class="source">	.dc.w	11926, 12269, 12616, 12966, 13318, 13674, 14031, 14391, 14753, 15117, 15482, 15849, 16216, 16585, 16954, 17324<br></td></tr
><tr
id=sl_svn23_166

><td class="source">	.dc.w	17694, 18064, 18433, 18802, 19171, 19539, 19905, 20271, 20634, 20996, 21356, 21714, 22069, 22422, 22772, 23118<br></td></tr
><tr
id=sl_svn23_167

><td class="source">	.dc.w	23462, 23802, 24138, 24471, 24799, 25123, 25443, 25758, 26068, 26373, 26673, 26967, 27256, 27539, 27816, 28087<br></td></tr
><tr
id=sl_svn23_168

><td class="source">	.dc.w	28352, 28610, 28862, 29107, 29345, 29576, 29800, 30017, 30226, 30428, 30622, 30808, 30987, 31157, 31319, 31473<br></td></tr
><tr
id=sl_svn23_169

><td class="source">	.dc.w	31619, 31756, 31885, 32006, 32117, 32220, 32315, 32400, 32477, 32545, 32603, 32653, 32694, 32726, 32748, 32762<br></td></tr
><tr
id=sl_svn23_170

><td class="source">	.dc.w	32766, 32762, 32748, 32726, 32694, 32653, 32603, 32545, 32477, 32400, 32315, 32221, 32117, 32006, 31885, 31757<br></td></tr
><tr
id=sl_svn23_171

><td class="source">	.dc.w	31619, 31473, 31319, 31157, 30987, 30808, 30622, 30428, 30226, 30017, 29800, 29576, 29345, 29107, 28862, 28610<br></td></tr
><tr
id=sl_svn23_172

><td class="source">	.dc.w	28352, 28087, 27816, 27539, 27256, 26967, 26673, 26373, 26068, 25758, 25443, 25123, 24799, 24471, 24138, 23802<br></td></tr
><tr
id=sl_svn23_173

><td class="source">	.dc.w	23462, 23118, 22772, 22422, 22069, 21714, 21356, 20996, 20634, 20271, 19905, 19539, 19171, 18803, 18433, 18064<br></td></tr
><tr
id=sl_svn23_174

><td class="source">	.dc.w	17694, 17324, 16954, 16585, 16216, 15849, 15482, 15117, 14753, 14391, 14031, 13674, 13318, 12966, 12616, 12269<br></td></tr
><tr
id=sl_svn23_175

><td class="source">	.dc.w	11926, 11586, 11249, 10917, 10588, 10264, 9945, 9630, 9320, 9015, 8715, 8420, 8132, 7849, 7571, 7300<br></td></tr
><tr
id=sl_svn23_176

><td class="source">	.dc.w	7036, 6777, 6526, 6280, 6042, 5811, 5587, 5370, 5161, 4959, 4765, 4579, 4401, 4230, 4068, 3914<br></td></tr
><tr
id=sl_svn23_177

><td class="source">	.dc.w	3768, 3631, 3502, 3382, 3270, 3167, 3073, 2987, 2910, 2843, 2784, 2734, 2693, 2662, 2639, 2625<br></td></tr
><tr
id=sl_svn23_178

><td class="source"><br></td></tr
><tr
id=sl_svn23_179

><td class="source">#elif FFT_N == 128<br></td></tr
><tr
id=sl_svn23_180

><td class="source">	.dc.w	2621, 2639, 2693, 2784, 2910, 3073, 3270, 3502, 3768, 4068, 4401, 4765, 5161, 5587, 6042, 6525<br></td></tr
><tr
id=sl_svn23_181

><td class="source">	.dc.w	7036, 7571, 8132, 8715, 9320, 9945, 10588, 11249, 11926, 12616, 13318, 14031, 14753, 15482, 16216, 16954<br></td></tr
><tr
id=sl_svn23_182

><td class="source">	.dc.w	17694, 18433, 19171, 19905, 20634, 21356, 22069, 22772, 23462, 24138, 24799, 25443, 26068, 26673, 27256, 27816<br></td></tr
><tr
id=sl_svn23_183

><td class="source">	.dc.w	28352, 28862, 29345, 29800, 30226, 30622, 30987, 31319, 31619, 31885, 32117, 32315, 32477, 32603, 32694, 32748<br></td></tr
><tr
id=sl_svn23_184

><td class="source">	.dc.w	32766, 32748, 32694, 32603, 32477, 32315, 32117, 31885, 31619, 31319, 30987, 30622, 30226, 29800, 29345, 28862<br></td></tr
><tr
id=sl_svn23_185

><td class="source">	.dc.w	28352, 27816, 27256, 26673, 26068, 25443, 24799, 24138, 23462, 22772, 22069, 21356, 20634, 19905, 19171, 18433<br></td></tr
><tr
id=sl_svn23_186

><td class="source">	.dc.w	17694, 16954, 16216, 15482, 14753, 14031, 13318, 12616, 11926, 11249, 10588, 9945, 9320, 8715, 8132, 7571<br></td></tr
><tr
id=sl_svn23_187

><td class="source">	.dc.w	7036, 6526, 6042, 5587, 5161, 4765, 4401, 4068, 3768, 3502, 3270, 3073, 2910, 2784, 2693, 2639<br></td></tr
><tr
id=sl_svn23_188

><td class="source"><br></td></tr
><tr
id=sl_svn23_189

><td class="source">#elif FFT_N == 64<br></td></tr
><tr
id=sl_svn23_190

><td class="source">	.dc.w	2621, 2693, 2910, 3270, 3768, 4401, 5161, 6042, 7036, 8132, 9320, 10588, 11926, 13318, 14753, 16216<br></td></tr
><tr
id=sl_svn23_191

><td class="source">	.dc.w	17694, 19171, 20634, 22069, 23462, 24799, 26068, 27256, 28352, 29345, 30226, 30987, 31619, 32117, 32477, 32694<br></td></tr
><tr
id=sl_svn23_192

><td class="source">	.dc.w	32766, 32694, 32477, 32117, 31619, 30987, 30226, 29345, 28352, 27256, 26068, 24799, 23462, 22069, 20634, 19171<br></td></tr
><tr
id=sl_svn23_193

><td class="source">	.dc.w	17694, 16216, 14753, 13318, 11926, 10588, 9320, 8132, 7036, 6042, 5161, 4401, 3768, 3270, 2910, 2693<br></td></tr
><tr
id=sl_svn23_194

><td class="source">#endif<br></td></tr
><tr
id=sl_svn23_195

><td class="source"><br></td></tr
><tr
id=sl_svn23_196

><td class="source"><br></td></tr
><tr
id=sl_svn23_197

><td class="source">tbl_cos_sin:	; Table of {cos(x),sin(x)}, (0 &lt;= x &lt; pi, in FFT_N/2 steps)<br></td></tr
><tr
id=sl_svn23_198

><td class="source">#if FFT_N == 1024<br></td></tr
><tr
id=sl_svn23_199

><td class="source">	.dc.w	32767, 0, 32766, 201, 32764, 402, 32761, 603, 32757, 804, 32751, 1005, 32744, 1206, 32736, 1406<br></td></tr
><tr
id=sl_svn23_200

><td class="source">	.dc.w	32727, 1607, 32717, 1808, 32705, 2009, 32692, 2209, 32678, 2410, 32662, 2610, 32646, 2811, 32628, 3011<br></td></tr
><tr
id=sl_svn23_201

><td class="source">	.dc.w	32609, 3211, 32588, 3411, 32567, 3611, 32544, 3811, 32520, 4011, 32495, 4210, 32468, 4409, 32441, 4608<br></td></tr
><tr
id=sl_svn23_202

><td class="source">	.dc.w	32412, 4807, 32382, 5006, 32350, 5205, 32318, 5403, 32284, 5601, 32249, 5799, 32213, 5997, 32176, 6195<br></td></tr
><tr
id=sl_svn23_203

><td class="source">	.dc.w	32137, 6392, 32097, 6589, 32056, 6786, 32014, 6982, 31970, 7179, 31926, 7375, 31880, 7571, 31833, 7766<br></td></tr
><tr
id=sl_svn23_204

><td class="source">	.dc.w	31785, 7961, 31735, 8156, 31684, 8351, 31633, 8545, 31580, 8739, 31525, 8932, 31470, 9126, 31413, 9319<br></td></tr
><tr
id=sl_svn23_205

><td class="source">	.dc.w	31356, 9511, 31297, 9703, 31236, 9895, 31175, 10087, 31113, 10278, 31049, 10469, 30984, 10659, 30918, 10849<br></td></tr
><tr
id=sl_svn23_206

><td class="source">	.dc.w	30851, 11038, 30783, 11227, 30713, 11416, 30643, 11604, 30571, 11792, 30498, 11980, 30424, 12166, 30349, 12353<br></td></tr
><tr
id=sl_svn23_207

><td class="source">	.dc.w	30272, 12539, 30195, 12724, 30116, 12909, 30036, 13094, 29955, 13278, 29873, 13462, 29790, 13645, 29706, 13827<br></td></tr
><tr
id=sl_svn23_208

><td class="source">	.dc.w	29621, 14009, 29534, 14191, 29446, 14372, 29358, 14552, 29268, 14732, 29177, 14911, 29085, 15090, 28992, 15268<br></td></tr
><tr
id=sl_svn23_209

><td class="source">	.dc.w	28897, 15446, 28802, 15623, 28706, 15799, 28608, 15975, 28510, 16150, 28410, 16325, 28309, 16499, 28208, 16672<br></td></tr
><tr
id=sl_svn23_210

><td class="source">	.dc.w	28105, 16845, 28001, 17017, 27896, 17189, 27790, 17360, 27683, 17530, 27575, 17699, 27466, 17868, 27355, 18036<br></td></tr
><tr
id=sl_svn23_211

><td class="source">	.dc.w	27244, 18204, 27132, 18371, 27019, 18537, 26905, 18702, 26789, 18867, 26673, 19031, 26556, 19194, 26437, 19357<br></td></tr
><tr
id=sl_svn23_212

><td class="source">	.dc.w	26318, 19519, 26198, 19680, 26077, 19840, 25954, 20000, 25831, 20159, 25707, 20317, 25582, 20474, 25456, 20631<br></td></tr
><tr
id=sl_svn23_213

><td class="source">	.dc.w	25329, 20787, 25201, 20942, 25072, 21096, 24942, 21249, 24811, 21402, 24679, 21554, 24546, 21705, 24413, 21855<br></td></tr
><tr
id=sl_svn23_214

><td class="source">	.dc.w	24278, 22004, 24143, 22153, 24006, 22301, 23869, 22448, 23731, 22594, 23592, 22739, 23452, 22883, 23311, 23027<br></td></tr
><tr
id=sl_svn23_215

><td class="source">	.dc.w	23169, 23169, 23027, 23311, 22883, 23452, 22739, 23592, 22594, 23731, 22448, 23869, 22301, 24006, 22153, 24143<br></td></tr
><tr
id=sl_svn23_216

><td class="source">	.dc.w	22004, 24278, 21855, 24413, 21705, 24546, 21554, 24679, 21402, 24811, 21249, 24942, 21096, 25072, 20942, 25201<br></td></tr
><tr
id=sl_svn23_217

><td class="source">	.dc.w	20787, 25329, 20631, 25456, 20474, 25582, 20317, 25707, 20159, 25831, 20000, 25954, 19840, 26077, 19680, 26198<br></td></tr
><tr
id=sl_svn23_218

><td class="source">	.dc.w	19519, 26318, 19357, 26437, 19194, 26556, 19031, 26673, 18867, 26789, 18702, 26905, 18537, 27019, 18371, 27132<br></td></tr
><tr
id=sl_svn23_219

><td class="source">	.dc.w	18204, 27244, 18036, 27355, 17868, 27466, 17699, 27575, 17530, 27683, 17360, 27790, 17189, 27896, 17017, 28001<br></td></tr
><tr
id=sl_svn23_220

><td class="source">	.dc.w	16845, 28105, 16672, 28208, 16499, 28309, 16325, 28410, 16150, 28510, 15975, 28608, 15799, 28706, 15623, 28802<br></td></tr
><tr
id=sl_svn23_221

><td class="source">	.dc.w	15446, 28897, 15268, 28992, 15090, 29085, 14911, 29177, 14732, 29268, 14552, 29358, 14372, 29446, 14191, 29534<br></td></tr
><tr
id=sl_svn23_222

><td class="source">	.dc.w	14009, 29621, 13827, 29706, 13645, 29790, 13462, 29873, 13278, 29955, 13094, 30036, 12909, 30116, 12724, 30195<br></td></tr
><tr
id=sl_svn23_223

><td class="source">	.dc.w	12539, 30272, 12353, 30349, 12166, 30424, 11980, 30498, 11792, 30571, 11604, 30643, 11416, 30713, 11227, 30783<br></td></tr
><tr
id=sl_svn23_224

><td class="source">	.dc.w	11038, 30851, 10849, 30918, 10659, 30984, 10469, 31049, 10278, 31113, 10087, 31175, 9895, 31236, 9704, 31297<br></td></tr
><tr
id=sl_svn23_225

><td class="source">	.dc.w	9511, 31356, 9319, 31413, 9126, 31470, 8933, 31525, 8739, 31580, 8545, 31633, 8351, 31684, 8156, 31735<br></td></tr
><tr
id=sl_svn23_226

><td class="source">	.dc.w	7961, 31785, 7766, 31833, 7571, 31880, 7375, 31926, 7179, 31970, 6983, 32014, 6786, 32056, 6589, 32097<br></td></tr
><tr
id=sl_svn23_227

><td class="source">	.dc.w	6392, 32137, 6195, 32176, 5997, 32213, 5799, 32249, 5601, 32284, 5403, 32318, 5205, 32350, 5006, 32382<br></td></tr
><tr
id=sl_svn23_228

><td class="source">	.dc.w	4807, 32412, 4608, 32441, 4409, 32468, 4210, 32495, 4011, 32520, 3811, 32544, 3611, 32567, 3411, 32588<br></td></tr
><tr
id=sl_svn23_229

><td class="source">	.dc.w	3211, 32609, 3011, 32628, 2811, 32646, 2610, 32662, 2410, 32678, 2209, 32692, 2009, 32705, 1808, 32717<br></td></tr
><tr
id=sl_svn23_230

><td class="source">	.dc.w	1607, 32727, 1407, 32736, 1206, 32744, 1005, 32751, 804, 32757, 603, 32761, 402, 32764, 201, 32766<br></td></tr
><tr
id=sl_svn23_231

><td class="source">	.dc.w	0, 32766, -201, 32766, -402, 32764, -603, 32761, -804, 32757, -1005, 32751, -1206, 32744, -1406, 32736<br></td></tr
><tr
id=sl_svn23_232

><td class="source">	.dc.w	-1607, 32727, -1808, 32717, -2009, 32705, -2209, 32692, -2410, 32678, -2610, 32662, -2811, 32646, -3011, 32628<br></td></tr
><tr
id=sl_svn23_233

><td class="source">	.dc.w	-3211, 32609, -3411, 32588, -3611, 32567, -3811, 32544, -4010, 32520, -4210, 32495, -4409, 32468, -4608, 32441<br></td></tr
><tr
id=sl_svn23_234

><td class="source">	.dc.w	-4807, 32412, -5006, 32382, -5205, 32350, -5403, 32318, -5601, 32284, -5799, 32249, -5997, 32213, -6195, 32176<br></td></tr
><tr
id=sl_svn23_235

><td class="source">	.dc.w	-6392, 32137, -6589, 32097, -6786, 32056, -6982, 32014, -7179, 31970, -7375, 31926, -7571, 31880, -7766, 31833<br></td></tr
><tr
id=sl_svn23_236

><td class="source">	.dc.w	-7961, 31785, -8156, 31735, -8351, 31684, -8545, 31633, -8739, 31580, -8932, 31525, -9126, 31470, -9319, 31413<br></td></tr
><tr
id=sl_svn23_237

><td class="source">	.dc.w	-9511, 31356, -9703, 31297, -9895, 31236, -10087, 31175, -10278, 31113, -10469, 31049, -10659, 30984, -10849, 30918<br></td></tr
><tr
id=sl_svn23_238

><td class="source">	.dc.w	-11038, 30851, -11227, 30783, -11416, 30713, -11604, 30643, -11792, 30571, -11979, 30498, -12166, 30424, -12353, 30349<br></td></tr
><tr
id=sl_svn23_239

><td class="source">	.dc.w	-12539, 30272, -12724, 30195, -12909, 30116, -13094, 30036, -13278, 29955, -13462, 29873, -13645, 29790, -13827, 29706<br></td></tr
><tr
id=sl_svn23_240

><td class="source">	.dc.w	-14009, 29621, -14191, 29534, -14372, 29446, -14552, 29358, -14732, 29268, -14911, 29177, -15090, 29085, -15268, 28992<br></td></tr
><tr
id=sl_svn23_241

><td class="source">	.dc.w	-15446, 28897, -15623, 28802, -15799, 28706, -15975, 28608, -16150, 28510, -16325, 28410, -16499, 28309, -16672, 28208<br></td></tr
><tr
id=sl_svn23_242

><td class="source">	.dc.w	-16845, 28105, -17017, 28001, -17189, 27896, -17360, 27790, -17530, 27683, -17699, 27575, -17868, 27466, -18036, 27355<br></td></tr
><tr
id=sl_svn23_243

><td class="source">	.dc.w	-18204, 27244, -18371, 27132, -18537, 27019, -18702, 26905, -18867, 26789, -19031, 26673, -19194, 26556, -19357, 26438<br></td></tr
><tr
id=sl_svn23_244

><td class="source">	.dc.w	-19519, 26318, -19680, 26198, -19840, 26077, -20000, 25954, -20159, 25831, -20317, 25707, -20474, 25582, -20631, 25456<br></td></tr
><tr
id=sl_svn23_245

><td class="source">	.dc.w	-20787, 25329, -20942, 25201, -21096, 25072, -21249, 24942, -21402, 24811, -21554, 24679, -21705, 24546, -21855, 24413<br></td></tr
><tr
id=sl_svn23_246

><td class="source">	.dc.w	-22004, 24278, -22153, 24143, -22301, 24006, -22448, 23869, -22594, 23731, -22739, 23592, -22883, 23452, -23027, 23311<br></td></tr
><tr
id=sl_svn23_247

><td class="source">	.dc.w	-23169, 23169, -23311, 23027, -23452, 22883, -23592, 22739, -23731, 22594, -23869, 22448, -24006, 22301, -24143, 22153<br></td></tr
><tr
id=sl_svn23_248

><td class="source">	.dc.w	-24278, 22005, -24413, 21855, -24546, 21705, -24679, 21554, -24811, 21402, -24942, 21249, -25072, 21096, -25201, 20942<br></td></tr
><tr
id=sl_svn23_249

><td class="source">	.dc.w	-25329, 20787, -25456, 20631, -25582, 20474, -25707, 20317, -25831, 20159, -25954, 20000, -26077, 19840, -26198, 19680<br></td></tr
><tr
id=sl_svn23_250

><td class="source">	.dc.w	-26318, 19519, -26437, 19357, -26556, 19194, -26673, 19031, -26789, 18867, -26905, 18702, -27019, 18537, -27132, 18371<br></td></tr
><tr
id=sl_svn23_251

><td class="source">	.dc.w	-27244, 18204, -27355, 18036, -27466, 17868, -27575, 17699, -27683, 17530, -27790, 17360, -27896, 17189, -28001, 17017<br></td></tr
><tr
id=sl_svn23_252

><td class="source">	.dc.w	-28105, 16845, -28207, 16672, -28309, 16499, -28410, 16325, -28510, 16150, -28608, 15975, -28706, 15799, -28802, 15623<br></td></tr
><tr
id=sl_svn23_253

><td class="source">	.dc.w	-28897, 15446, -28992, 15268, -29085, 15090, -29177, 14911, -29268, 14732, -29358, 14552, -29446, 14372, -29534, 14191<br></td></tr
><tr
id=sl_svn23_254

><td class="source">	.dc.w	-29620, 14009, -29706, 13827, -29790, 13645, -29873, 13462, -29955, 13278, -30036, 13094, -30116, 12910, -30195, 12724<br></td></tr
><tr
id=sl_svn23_255

><td class="source">	.dc.w	-30272, 12539, -30349, 12353, -30424, 12167, -30498, 11980, -30571, 11792, -30643, 11604, -30713, 11416, -30783, 11228<br></td></tr
><tr
id=sl_svn23_256

><td class="source">	.dc.w	-30851, 11038, -30918, 10849, -30984, 10659, -31049, 10469, -31113, 10278, -31175, 10087, -31236, 9895, -31297, 9704<br></td></tr
><tr
id=sl_svn23_257

><td class="source">	.dc.w	-31356, 9511, -31413, 9319, -31470, 9126, -31525, 8933, -31580, 8739, -31633, 8545, -31684, 8351, -31735, 8156<br></td></tr
><tr
id=sl_svn23_258

><td class="source">	.dc.w	-31784, 7961, -31833, 7766, -31880, 7571, -31926, 7375, -31970, 7179, -32014, 6983, -32056, 6786, -32097, 6589<br></td></tr
><tr
id=sl_svn23_259

><td class="source">	.dc.w	-32137, 6392, -32175, 6195, -32213, 5997, -32249, 5799, -32284, 5601, -32318, 5403, -32350, 5205, -32382, 5006<br></td></tr
><tr
id=sl_svn23_260

><td class="source">	.dc.w	-32412, 4807, -32441, 4609, -32468, 4409, -32495, 4210, -32520, 4011, -32544, 3811, -32567, 3611, -32588, 3411<br></td></tr
><tr
id=sl_svn23_261

><td class="source">	.dc.w	-32609, 3211, -32628, 3011, -32646, 2811, -32662, 2611, -32678, 2410, -32692, 2210, -32705, 2009, -32717, 1808<br></td></tr
><tr
id=sl_svn23_262

><td class="source">	.dc.w	-32727, 1607, -32736, 1407, -32744, 1206, -32751, 1005, -32757, 804, -32761, 603, -32764, 402, -32766, 201<br></td></tr
><tr
id=sl_svn23_263

><td class="source"><br></td></tr
><tr
id=sl_svn23_264

><td class="source">#elif FFT_N == 512<br></td></tr
><tr
id=sl_svn23_265

><td class="source">	.dc.w	32767, 0, 32764, 402, 32757, 804, 32744, 1206, 32727, 1607, 32705, 2009, 32678, 2410, 32646, 2811<br></td></tr
><tr
id=sl_svn23_266

><td class="source">	.dc.w	32609, 3211, 32567, 3611, 32520, 4011, 32468, 4409, 32412, 4807, 32350, 5205, 32284, 5601, 32213, 5997<br></td></tr
><tr
id=sl_svn23_267

><td class="source">	.dc.w	32137, 6392, 32056, 6786, 31970, 7179, 31880, 7571, 31785, 7961, 31684, 8351, 31580, 8739, 31470, 9126<br></td></tr
><tr
id=sl_svn23_268

><td class="source">	.dc.w	31356, 9511, 31236, 9895, 31113, 10278, 30984, 10659, 30851, 11038, 30713, 11416, 30571, 11792, 30424, 12166<br></td></tr
><tr
id=sl_svn23_269

><td class="source">	.dc.w	30272, 12539, 30116, 12909, 29955, 13278, 29790, 13645, 29621, 14009, 29446, 14372, 29268, 14732, 29085, 15090<br></td></tr
><tr
id=sl_svn23_270

><td class="source">	.dc.w	28897, 15446, 28706, 15799, 28510, 16150, 28309, 16499, 28105, 16845, 27896, 17189, 27683, 17530, 27466, 17868<br></td></tr
><tr
id=sl_svn23_271

><td class="source">	.dc.w	27244, 18204, 27019, 18537, 26789, 18867, 26556, 19194, 26318, 19519, 26077, 19840, 25831, 20159, 25582, 20474<br></td></tr
><tr
id=sl_svn23_272

><td class="source">	.dc.w	25329, 20787, 25072, 21096, 24811, 21402, 24546, 21705, 24278, 22004, 24006, 22301, 23731, 22594, 23452, 22883<br></td></tr
><tr
id=sl_svn23_273

><td class="source">	.dc.w	23169, 23169, 22883, 23452, 22594, 23731, 22301, 24006, 22004, 24278, 21705, 24546, 21402, 24811, 21096, 25072<br></td></tr
><tr
id=sl_svn23_274

><td class="source">	.dc.w	20787, 25329, 20474, 25582, 20159, 25831, 19840, 26077, 19519, 26318, 19194, 26556, 18867, 26789, 18537, 27019<br></td></tr
><tr
id=sl_svn23_275

><td class="source">	.dc.w	18204, 27244, 17868, 27466, 17530, 27683, 17189, 27896, 16845, 28105, 16499, 28309, 16150, 28510, 15799, 28706<br></td></tr
><tr
id=sl_svn23_276

><td class="source">	.dc.w	15446, 28897, 15090, 29085, 14732, 29268, 14372, 29446, 14009, 29621, 13645, 29790, 13278, 29955, 12909, 30116<br></td></tr
><tr
id=sl_svn23_277

><td class="source">	.dc.w	12539, 30272, 12166, 30424, 11792, 30571, 11416, 30713, 11038, 30851, 10659, 30984, 10278, 31113, 9895, 31236<br></td></tr
><tr
id=sl_svn23_278

><td class="source">	.dc.w	9511, 31356, 9126, 31470, 8739, 31580, 8351, 31684, 7961, 31785, 7571, 31880, 7179, 31970, 6786, 32056<br></td></tr
><tr
id=sl_svn23_279

><td class="source">	.dc.w	6392, 32137, 5997, 32213, 5601, 32284, 5205, 32350, 4807, 32412, 4409, 32468, 4011, 32520, 3611, 32567<br></td></tr
><tr
id=sl_svn23_280

><td class="source">	.dc.w	3211, 32609, 2811, 32646, 2410, 32678, 2009, 32705, 1607, 32727, 1206, 32744, 804, 32757, 402, 32764<br></td></tr
><tr
id=sl_svn23_281

><td class="source">	.dc.w	0, 32766, -402, 32764, -804, 32757, -1206, 32744, -1607, 32727, -2009, 32705, -2410, 32678, -2811, 32646<br></td></tr
><tr
id=sl_svn23_282

><td class="source">	.dc.w	-3211, 32609, -3611, 32567, -4010, 32520, -4409, 32468, -4807, 32412, -5205, 32350, -5601, 32284, -5997, 32213<br></td></tr
><tr
id=sl_svn23_283

><td class="source">	.dc.w	-6392, 32137, -6786, 32056, -7179, 31970, -7571, 31880, -7961, 31785, -8351, 31684, -8739, 31580, -9126, 31470<br></td></tr
><tr
id=sl_svn23_284

><td class="source">	.dc.w	-9511, 31356, -9895, 31236, -10278, 31113, -10659, 30984, -11038, 30851, -11416, 30713, -11792, 30571, -12166, 30424<br></td></tr
><tr
id=sl_svn23_285

><td class="source">	.dc.w	-12539, 30272, -12909, 30116, -13278, 29955, -13645, 29790, -14009, 29621, -14372, 29446, -14732, 29268, -15090, 29085<br></td></tr
><tr
id=sl_svn23_286

><td class="source">	.dc.w	-15446, 28897, -15799, 28706, -16150, 28510, -16499, 28309, -16845, 28105, -17189, 27896, -17530, 27683, -17868, 27466<br></td></tr
><tr
id=sl_svn23_287

><td class="source">	.dc.w	-18204, 27244, -18537, 27019, -18867, 26789, -19194, 26556, -19519, 26318, -19840, 26077, -20159, 25831, -20474, 25582<br></td></tr
><tr
id=sl_svn23_288

><td class="source">	.dc.w	-20787, 25329, -21096, 25072, -21402, 24811, -21705, 24546, -22004, 24278, -22301, 24006, -22594, 23731, -22883, 23452<br></td></tr
><tr
id=sl_svn23_289

><td class="source">	.dc.w	-23169, 23169, -23452, 22883, -23731, 22594, -24006, 22301, -24278, 22005, -24546, 21705, -24811, 21402, -25072, 21096<br></td></tr
><tr
id=sl_svn23_290

><td class="source">	.dc.w	-25329, 20787, -25582, 20474, -25831, 20159, -26077, 19840, -26318, 19519, -26556, 19194, -26789, 18867, -27019, 18537<br></td></tr
><tr
id=sl_svn23_291

><td class="source">	.dc.w	-27244, 18204, -27466, 17868, -27683, 17530, -27896, 17189, -28105, 16845, -28309, 16499, -28510, 16150, -28706, 15799<br></td></tr
><tr
id=sl_svn23_292

><td class="source">	.dc.w	-28897, 15446, -29085, 15090, -29268, 14732, -29446, 14372, -29620, 14009, -29790, 13645, -29955, 13278, -30116, 12910<br></td></tr
><tr
id=sl_svn23_293

><td class="source">	.dc.w	-30272, 12539, -30424, 12167, -30571, 11792, -30713, 11416, -30851, 11038, -30984, 10659, -31113, 10278, -31236, 9895<br></td></tr
><tr
id=sl_svn23_294

><td class="source">	.dc.w	-31356, 9511, -31470, 9126, -31580, 8739, -31684, 8351, -31784, 7961, -31880, 7571, -31970, 7179, -32056, 6786<br></td></tr
><tr
id=sl_svn23_295

><td class="source">	.dc.w	-32137, 6392, -32213, 5997, -32284, 5601, -32350, 5205, -32412, 4807, -32468, 4409, -32520, 4011, -32567, 3611<br></td></tr
><tr
id=sl_svn23_296

><td class="source">	.dc.w	-32609, 3211, -32646, 2811, -32678, 2410, -32705, 2009, -32727, 1607, -32744, 1206, -32757, 804, -32764, 402<br></td></tr
><tr
id=sl_svn23_297

><td class="source"><br></td></tr
><tr
id=sl_svn23_298

><td class="source">#elif FFT_N == 256<br></td></tr
><tr
id=sl_svn23_299

><td class="source">	.dc.w	32767, 0, 32757, 804, 32727, 1607, 32678, 2410, 32609, 3211, 32520, 4011, 32412, 4807, 32284, 5601<br></td></tr
><tr
id=sl_svn23_300

><td class="source">	.dc.w	32137, 6392, 31970, 7179, 31785, 7961, 31580, 8739, 31356, 9511, 31113, 10278, 30851, 11038, 30571, 11792<br></td></tr
><tr
id=sl_svn23_301

><td class="source">	.dc.w	30272, 12539, 29955, 13278, 29621, 14009, 29268, 14732, 28897, 15446, 28510, 16150, 28105, 16845, 27683, 17530<br></td></tr
><tr
id=sl_svn23_302

><td class="source">	.dc.w	27244, 18204, 26789, 18867, 26318, 19519, 25831, 20159, 25329, 20787, 24811, 21402, 24278, 22004, 23731, 22594<br></td></tr
><tr
id=sl_svn23_303

><td class="source">	.dc.w	23169, 23169, 22594, 23731, 22004, 24278, 21402, 24811, 20787, 25329, 20159, 25831, 19519, 26318, 18867, 26789<br></td></tr
><tr
id=sl_svn23_304

><td class="source">	.dc.w	18204, 27244, 17530, 27683, 16845, 28105, 16150, 28510, 15446, 28897, 14732, 29268, 14009, 29621, 13278, 29955<br></td></tr
><tr
id=sl_svn23_305

><td class="source">	.dc.w	12539, 30272, 11792, 30571, 11038, 30851, 10278, 31113, 9511, 31356, 8739, 31580, 7961, 31785, 7179, 31970<br></td></tr
><tr
id=sl_svn23_306

><td class="source">	.dc.w	6392, 32137, 5601, 32284, 4807, 32412, 4011, 32520, 3211, 32609, 2410, 32678, 1607, 32727, 804, 32757<br></td></tr
><tr
id=sl_svn23_307

><td class="source">	.dc.w	0, 32766, -804, 32757, -1607, 32727, -2410, 32678, -3211, 32609, -4010, 32520, -4807, 32412, -5601, 32284<br></td></tr
><tr
id=sl_svn23_308

><td class="source">	.dc.w	-6392, 32137, -7179, 31970, -7961, 31785, -8739, 31580, -9511, 31356, -10278, 31113, -11038, 30851, -11792, 30571<br></td></tr
><tr
id=sl_svn23_309

><td class="source">	.dc.w	-12539, 30272, -13278, 29955, -14009, 29621, -14732, 29268, -15446, 28897, -16150, 28510, -16845, 28105, -17530, 27683<br></td></tr
><tr
id=sl_svn23_310

><td class="source">	.dc.w	-18204, 27244, -18867, 26789, -19519, 26318, -20159, 25831, -20787, 25329, -21402, 24811, -22004, 24278, -22594, 23731<br></td></tr
><tr
id=sl_svn23_311

><td class="source">	.dc.w	-23169, 23169, -23731, 22594, -24278, 22005, -24811, 21402, -25329, 20787, -25831, 20159, -26318, 19519, -26789, 18867<br></td></tr
><tr
id=sl_svn23_312

><td class="source">	.dc.w	-27244, 18204, -27683, 17530, -28105, 16845, -28510, 16150, -28897, 15446, -29268, 14732, -29620, 14009, -29955, 13278<br></td></tr
><tr
id=sl_svn23_313

><td class="source">	.dc.w	-30272, 12539, -30571, 11792, -30851, 11038, -31113, 10278, -31356, 9511, -31580, 8739, -31784, 7961, -31970, 7179<br></td></tr
><tr
id=sl_svn23_314

><td class="source">	.dc.w	-32137, 6392, -32284, 5601, -32412, 4807, -32520, 4011, -32609, 3211, -32678, 2410, -32727, 1607, -32757, 804<br></td></tr
><tr
id=sl_svn23_315

><td class="source"><br></td></tr
><tr
id=sl_svn23_316

><td class="source">#elif FFT_N == 128<br></td></tr
><tr
id=sl_svn23_317

><td class="source">	.dc.w	32767, 0, 32727, 1607, 32609, 3211, 32412, 4807, 32137, 6392, 31785, 7961, 31356, 9511, 30851, 11038<br></td></tr
><tr
id=sl_svn23_318

><td class="source">	.dc.w	30272, 12539, 29621, 14009, 28897, 15446, 28105, 16845, 27244, 18204, 26318, 19519, 25329, 20787, 24278, 22004<br></td></tr
><tr
id=sl_svn23_319

><td class="source">	.dc.w	23169, 23169, 22004, 24278, 20787, 25329, 19519, 26318, 18204, 27244, 16845, 28105, 15446, 28897, 14009, 29621<br></td></tr
><tr
id=sl_svn23_320

><td class="source">	.dc.w	12539, 30272, 11038, 30851, 9511, 31356, 7961, 31785, 6392, 32137, 4807, 32412, 3211, 32609, 1607, 32727<br></td></tr
><tr
id=sl_svn23_321

><td class="source">	.dc.w	0, 32766, -1607, 32727, -3211, 32609, -4807, 32412, -6392, 32137, -7961, 31785, -9511, 31356, -11038, 30851<br></td></tr
><tr
id=sl_svn23_322

><td class="source">	.dc.w	-12539, 30272, -14009, 29621, -15446, 28897, -16845, 28105, -18204, 27244, -19519, 26318, -20787, 25329, -22004, 24278<br></td></tr
><tr
id=sl_svn23_323

><td class="source">	.dc.w	-23169, 23169, -24278, 22005, -25329, 20787, -26318, 19519, -27244, 18204, -28105, 16845, -28897, 15446, -29620, 14009<br></td></tr
><tr
id=sl_svn23_324

><td class="source">	.dc.w	-30272, 12539, -30851, 11038, -31356, 9511, -31784, 7961, -32137, 6392, -32412, 4807, -32609, 3211, -32727, 1607<br></td></tr
><tr
id=sl_svn23_325

><td class="source"><br></td></tr
><tr
id=sl_svn23_326

><td class="source">#elif FFT_N == 64<br></td></tr
><tr
id=sl_svn23_327

><td class="source">	.dc.w	32767, 0, 32609, 3211, 32137, 6392, 31356, 9511, 30272, 12539, 28897, 15446, 27244, 18204, 25329, 20787<br></td></tr
><tr
id=sl_svn23_328

><td class="source">	.dc.w	23169, 23169, 20787, 25329, 18204, 27244, 15446, 28897, 12539, 30272, 9511, 31356, 6392, 32137, 3211, 32609<br></td></tr
><tr
id=sl_svn23_329

><td class="source">	.dc.w	0, 32766, -3211, 32609, -6392, 32137, -9511, 31356, -12539, 30272, -15446, 28897, -18204, 27244, -20787, 25329<br></td></tr
><tr
id=sl_svn23_330

><td class="source">	.dc.w	-23169, 23169, -25329, 20787, -27244, 18204, -28897, 15446, -30272, 12539, -31356, 9511, -32137, 6392, -32609, 3211<br></td></tr
><tr
id=sl_svn23_331

><td class="source">#endif<br></td></tr
><tr
id=sl_svn23_332

><td class="source"><br></td></tr
><tr
id=sl_svn23_333

><td class="source"><br></td></tr
><tr
id=sl_svn23_334

><td class="source"><br></td></tr
><tr
id=sl_svn23_335

><td class="source">tbl_bitrev:		; tbl_bitrev[] = ...<br></td></tr
><tr
id=sl_svn23_336

><td class="source">#if FFT_N == 1024<br></td></tr
><tr
id=sl_svn23_337

><td class="source">#ifdef INPUT_IQ<br></td></tr
><tr
id=sl_svn23_338

><td class="source">	.dc.w	1*4, 513*4, 257*4, 769*4, 129*4, 641*4, 385*4, 897*4, 65*4, 577*4, 321*4, 833*4, 193*4, 705*4, 449*4, 961*4<br></td></tr
><tr
id=sl_svn23_339

><td class="source">	.dc.w	33*4, 545*4, 289*4, 801*4, 161*4, 673*4, 417*4, 929*4, 97*4, 609*4, 353*4, 865*4, 225*4, 737*4, 481*4, 993*4<br></td></tr
><tr
id=sl_svn23_340

><td class="source">	.dc.w	17*4, 529*4, 273*4, 785*4, 145*4, 657*4, 401*4, 913*4, 81*4, 593*4, 337*4, 849*4, 209*4, 721*4, 465*4, 977*4<br></td></tr
><tr
id=sl_svn23_341

><td class="source">	.dc.w	49*4, 561*4, 305*4, 817*4, 177*4, 689*4, 433*4, 945*4, 113*4, 625*4, 369*4, 881*4, 241*4, 753*4, 497*4, 1009*4<br></td></tr
><tr
id=sl_svn23_342

><td class="source">	.dc.w	9*4, 521*4, 265*4, 777*4, 137*4, 649*4, 393*4, 905*4, 73*4, 585*4, 329*4, 841*4, 201*4, 713*4, 457*4, 969*4<br></td></tr
><tr
id=sl_svn23_343

><td class="source">	.dc.w	41*4, 553*4, 297*4, 809*4, 169*4, 681*4, 425*4, 937*4, 105*4, 617*4, 361*4, 873*4, 233*4, 745*4, 489*4, 1001*4<br></td></tr
><tr
id=sl_svn23_344

><td class="source">	.dc.w	25*4, 537*4, 281*4, 793*4, 153*4, 665*4, 409*4, 921*4, 89*4, 601*4, 345*4, 857*4, 217*4, 729*4, 473*4, 985*4<br></td></tr
><tr
id=sl_svn23_345

><td class="source">	.dc.w	57*4, 569*4, 313*4, 825*4, 185*4, 697*4, 441*4, 953*4, 121*4, 633*4, 377*4, 889*4, 249*4, 761*4, 505*4, 1017*4<br></td></tr
><tr
id=sl_svn23_346

><td class="source">	.dc.w	5*4, 517*4, 261*4, 773*4, 133*4, 645*4, 389*4, 901*4, 69*4, 581*4, 325*4, 837*4, 197*4, 709*4, 453*4, 965*4<br></td></tr
><tr
id=sl_svn23_347

><td class="source">	.dc.w	37*4, 549*4, 293*4, 805*4, 165*4, 677*4, 421*4, 933*4, 101*4, 613*4, 357*4, 869*4, 229*4, 741*4, 485*4, 997*4<br></td></tr
><tr
id=sl_svn23_348

><td class="source">	.dc.w	21*4, 533*4, 277*4, 789*4, 149*4, 661*4, 405*4, 917*4, 85*4, 597*4, 341*4, 853*4, 213*4, 725*4, 469*4, 981*4<br></td></tr
><tr
id=sl_svn23_349

><td class="source">	.dc.w	53*4, 565*4, 309*4, 821*4, 181*4, 693*4, 437*4, 949*4, 117*4, 629*4, 373*4, 885*4, 245*4, 757*4, 501*4, 1013*4<br></td></tr
><tr
id=sl_svn23_350

><td class="source">	.dc.w	13*4, 525*4, 269*4, 781*4, 141*4, 653*4, 397*4, 909*4, 77*4, 589*4, 333*4, 845*4, 205*4, 717*4, 461*4, 973*4<br></td></tr
><tr
id=sl_svn23_351

><td class="source">	.dc.w	45*4, 557*4, 301*4, 813*4, 173*4, 685*4, 429*4, 941*4, 109*4, 621*4, 365*4, 877*4, 237*4, 749*4, 493*4, 1005*4<br></td></tr
><tr
id=sl_svn23_352

><td class="source">	.dc.w	29*4, 541*4, 285*4, 797*4, 157*4, 669*4, 413*4, 925*4, 93*4, 605*4, 349*4, 861*4, 221*4, 733*4, 477*4, 989*4<br></td></tr
><tr
id=sl_svn23_353

><td class="source">	.dc.w	61*4, 573*4, 317*4, 829*4, 189*4, 701*4, 445*4, 957*4, 125*4, 637*4, 381*4, 893*4, 253*4, 765*4, 509*4, 1021*4<br></td></tr
><tr
id=sl_svn23_354

><td class="source">	.dc.w	3*4, 515*4, 259*4, 771*4, 131*4, 643*4, 387*4, 899*4, 67*4, 579*4, 323*4, 835*4, 195*4, 707*4, 451*4, 963*4<br></td></tr
><tr
id=sl_svn23_355

><td class="source">	.dc.w	35*4, 547*4, 291*4, 803*4, 163*4, 675*4, 419*4, 931*4, 99*4, 611*4, 355*4, 867*4, 227*4, 739*4, 483*4, 995*4<br></td></tr
><tr
id=sl_svn23_356

><td class="source">	.dc.w	19*4, 531*4, 275*4, 787*4, 147*4, 659*4, 403*4, 915*4, 83*4, 595*4, 339*4, 851*4, 211*4, 723*4, 467*4, 979*4<br></td></tr
><tr
id=sl_svn23_357

><td class="source">	.dc.w	51*4, 563*4, 307*4, 819*4, 179*4, 691*4, 435*4, 947*4, 115*4, 627*4, 371*4, 883*4, 243*4, 755*4, 499*4, 1011*4<br></td></tr
><tr
id=sl_svn23_358

><td class="source">	.dc.w	11*4, 523*4, 267*4, 779*4, 139*4, 651*4, 395*4, 907*4, 75*4, 587*4, 331*4, 843*4, 203*4, 715*4, 459*4, 971*4<br></td></tr
><tr
id=sl_svn23_359

><td class="source">	.dc.w	43*4, 555*4, 299*4, 811*4, 171*4, 683*4, 427*4, 939*4, 107*4, 619*4, 363*4, 875*4, 235*4, 747*4, 491*4, 1003*4<br></td></tr
><tr
id=sl_svn23_360

><td class="source">	.dc.w	27*4, 539*4, 283*4, 795*4, 155*4, 667*4, 411*4, 923*4, 91*4, 603*4, 347*4, 859*4, 219*4, 731*4, 475*4, 987*4<br></td></tr
><tr
id=sl_svn23_361

><td class="source">	.dc.w	59*4, 571*4, 315*4, 827*4, 187*4, 699*4, 443*4, 955*4, 123*4, 635*4, 379*4, 891*4, 251*4, 763*4, 507*4, 1019*4<br></td></tr
><tr
id=sl_svn23_362

><td class="source">	.dc.w	7*4, 519*4, 263*4, 775*4, 135*4, 647*4, 391*4, 903*4, 71*4, 583*4, 327*4, 839*4, 199*4, 711*4, 455*4, 967*4<br></td></tr
><tr
id=sl_svn23_363

><td class="source">	.dc.w	39*4, 551*4, 295*4, 807*4, 167*4, 679*4, 423*4, 935*4, 103*4, 615*4, 359*4, 871*4, 231*4, 743*4, 487*4, 999*4<br></td></tr
><tr
id=sl_svn23_364

><td class="source">	.dc.w	23*4, 535*4, 279*4, 791*4, 151*4, 663*4, 407*4, 919*4, 87*4, 599*4, 343*4, 855*4, 215*4, 727*4, 471*4, 983*4<br></td></tr
><tr
id=sl_svn23_365

><td class="source">	.dc.w	55*4, 567*4, 311*4, 823*4, 183*4, 695*4, 439*4, 951*4, 119*4, 631*4, 375*4, 887*4, 247*4, 759*4, 503*4, 1015*4<br></td></tr
><tr
id=sl_svn23_366

><td class="source">	.dc.w	15*4, 527*4, 271*4, 783*4, 143*4, 655*4, 399*4, 911*4, 79*4, 591*4, 335*4, 847*4, 207*4, 719*4, 463*4, 975*4<br></td></tr
><tr
id=sl_svn23_367

><td class="source">	.dc.w	47*4, 559*4, 303*4, 815*4, 175*4, 687*4, 431*4, 943*4, 111*4, 623*4, 367*4, 879*4, 239*4, 751*4, 495*4, 1007*4<br></td></tr
><tr
id=sl_svn23_368

><td class="source">	.dc.w	31*4, 543*4, 287*4, 799*4, 159*4, 671*4, 415*4, 927*4, 95*4, 607*4, 351*4, 863*4, 223*4, 735*4, 479*4, 991*4<br></td></tr
><tr
id=sl_svn23_369

><td class="source">	.dc.w	63*4, 575*4, 319*4, 831*4, 191*4, 703*4, 447*4, 959*4, 127*4, 639*4, 383*4, 895*4, 255*4, 767*4, 511*4, 1023*4<br></td></tr
><tr
id=sl_svn23_370

><td class="source">#endif<br></td></tr
><tr
id=sl_svn23_371

><td class="source">	.dc.w	0*4, 512*4, 256*4, 768*4, 128*4, 640*4, 384*4, 896*4, 64*4, 576*4, 320*4, 832*4, 192*4, 704*4, 448*4, 960*4<br></td></tr
><tr
id=sl_svn23_372

><td class="source">	.dc.w	32*4, 544*4, 288*4, 800*4, 160*4, 672*4, 416*4, 928*4, 96*4, 608*4, 352*4, 864*4, 224*4, 736*4, 480*4, 992*4<br></td></tr
><tr
id=sl_svn23_373

><td class="source">	.dc.w	16*4, 528*4, 272*4, 784*4, 144*4, 656*4, 400*4, 912*4, 80*4, 592*4, 336*4, 848*4, 208*4, 720*4, 464*4, 976*4<br></td></tr
><tr
id=sl_svn23_374

><td class="source">	.dc.w	48*4, 560*4, 304*4, 816*4, 176*4, 688*4, 432*4, 944*4, 112*4, 624*4, 368*4, 880*4, 240*4, 752*4, 496*4, 1008*4<br></td></tr
><tr
id=sl_svn23_375

><td class="source">	.dc.w	8*4, 520*4, 264*4, 776*4, 136*4, 648*4, 392*4, 904*4, 72*4, 584*4, 328*4, 840*4, 200*4, 712*4, 456*4, 968*4<br></td></tr
><tr
id=sl_svn23_376

><td class="source">	.dc.w	40*4, 552*4, 296*4, 808*4, 168*4, 680*4, 424*4, 936*4, 104*4, 616*4, 360*4, 872*4, 232*4, 744*4, 488*4, 1000*4<br></td></tr
><tr
id=sl_svn23_377

><td class="source">	.dc.w	24*4, 536*4, 280*4, 792*4, 152*4, 664*4, 408*4, 920*4, 88*4, 600*4, 344*4, 856*4, 216*4, 728*4, 472*4, 984*4<br></td></tr
><tr
id=sl_svn23_378

><td class="source">	.dc.w	56*4, 568*4, 312*4, 824*4, 184*4, 696*4, 440*4, 952*4, 120*4, 632*4, 376*4, 888*4, 248*4, 760*4, 504*4, 1016*4<br></td></tr
><tr
id=sl_svn23_379

><td class="source">	.dc.w	4*4, 516*4, 260*4, 772*4, 132*4, 644*4, 388*4, 900*4, 68*4, 580*4, 324*4, 836*4, 196*4, 708*4, 452*4, 964*4<br></td></tr
><tr
id=sl_svn23_380

><td class="source">	.dc.w	36*4, 548*4, 292*4, 804*4, 164*4, 676*4, 420*4, 932*4, 100*4, 612*4, 356*4, 868*4, 228*4, 740*4, 484*4, 996*4<br></td></tr
><tr
id=sl_svn23_381

><td class="source">	.dc.w	20*4, 532*4, 276*4, 788*4, 148*4, 660*4, 404*4, 916*4, 84*4, 596*4, 340*4, 852*4, 212*4, 724*4, 468*4, 980*4<br></td></tr
><tr
id=sl_svn23_382

><td class="source">	.dc.w	52*4, 564*4, 308*4, 820*4, 180*4, 692*4, 436*4, 948*4, 116*4, 628*4, 372*4, 884*4, 244*4, 756*4, 500*4, 1012*4<br></td></tr
><tr
id=sl_svn23_383

><td class="source">	.dc.w	12*4, 524*4, 268*4, 780*4, 140*4, 652*4, 396*4, 908*4, 76*4, 588*4, 332*4, 844*4, 204*4, 716*4, 460*4, 972*4<br></td></tr
><tr
id=sl_svn23_384

><td class="source">	.dc.w	44*4, 556*4, 300*4, 812*4, 172*4, 684*4, 428*4, 940*4, 108*4, 620*4, 364*4, 876*4, 236*4, 748*4, 492*4, 1004*4<br></td></tr
><tr
id=sl_svn23_385

><td class="source">	.dc.w	28*4, 540*4, 284*4, 796*4, 156*4, 668*4, 412*4, 924*4, 92*4, 604*4, 348*4, 860*4, 220*4, 732*4, 476*4, 988*4<br></td></tr
><tr
id=sl_svn23_386

><td class="source">	.dc.w	60*4, 572*4, 316*4, 828*4, 188*4, 700*4, 444*4, 956*4, 124*4, 636*4, 380*4, 892*4, 252*4, 764*4, 508*4, 1020*4<br></td></tr
><tr
id=sl_svn23_387

><td class="source">	.dc.w	2*4, 514*4, 258*4, 770*4, 130*4, 642*4, 386*4, 898*4, 66*4, 578*4, 322*4, 834*4, 194*4, 706*4, 450*4, 962*4<br></td></tr
><tr
id=sl_svn23_388

><td class="source">	.dc.w	34*4, 546*4, 290*4, 802*4, 162*4, 674*4, 418*4, 930*4, 98*4, 610*4, 354*4, 866*4, 226*4, 738*4, 482*4, 994*4<br></td></tr
><tr
id=sl_svn23_389

><td class="source">	.dc.w	18*4, 530*4, 274*4, 786*4, 146*4, 658*4, 402*4, 914*4, 82*4, 594*4, 338*4, 850*4, 210*4, 722*4, 466*4, 978*4<br></td></tr
><tr
id=sl_svn23_390

><td class="source">	.dc.w	50*4, 562*4, 306*4, 818*4, 178*4, 690*4, 434*4, 946*4, 114*4, 626*4, 370*4, 882*4, 242*4, 754*4, 498*4, 1010*4<br></td></tr
><tr
id=sl_svn23_391

><td class="source">	.dc.w	10*4, 522*4, 266*4, 778*4, 138*4, 650*4, 394*4, 906*4, 74*4, 586*4, 330*4, 842*4, 202*4, 714*4, 458*4, 970*4<br></td></tr
><tr
id=sl_svn23_392

><td class="source">	.dc.w	42*4, 554*4, 298*4, 810*4, 170*4, 682*4, 426*4, 938*4, 106*4, 618*4, 362*4, 874*4, 234*4, 746*4, 490*4, 1002*4<br></td></tr
><tr
id=sl_svn23_393

><td class="source">	.dc.w	26*4, 538*4, 282*4, 794*4, 154*4, 666*4, 410*4, 922*4, 90*4, 602*4, 346*4, 858*4, 218*4, 730*4, 474*4, 986*4<br></td></tr
><tr
id=sl_svn23_394

><td class="source">	.dc.w	58*4, 570*4, 314*4, 826*4, 186*4, 698*4, 442*4, 954*4, 122*4, 634*4, 378*4, 890*4, 250*4, 762*4, 506*4, 1018*4<br></td></tr
><tr
id=sl_svn23_395

><td class="source">	.dc.w	6*4, 518*4, 262*4, 774*4, 134*4, 646*4, 390*4, 902*4, 70*4, 582*4, 326*4, 838*4, 198*4, 710*4, 454*4, 966*4<br></td></tr
><tr
id=sl_svn23_396

><td class="source">	.dc.w	38*4, 550*4, 294*4, 806*4, 166*4, 678*4, 422*4, 934*4, 102*4, 614*4, 358*4, 870*4, 230*4, 742*4, 486*4, 998*4<br></td></tr
><tr
id=sl_svn23_397

><td class="source">	.dc.w	22*4, 534*4, 278*4, 790*4, 150*4, 662*4, 406*4, 918*4, 86*4, 598*4, 342*4, 854*4, 214*4, 726*4, 470*4, 982*4<br></td></tr
><tr
id=sl_svn23_398

><td class="source">	.dc.w	54*4, 566*4, 310*4, 822*4, 182*4, 694*4, 438*4, 950*4, 118*4, 630*4, 374*4, 886*4, 246*4, 758*4, 502*4, 1014*4<br></td></tr
><tr
id=sl_svn23_399

><td class="source">	.dc.w	14*4, 526*4, 270*4, 782*4, 142*4, 654*4, 398*4, 910*4, 78*4, 590*4, 334*4, 846*4, 206*4, 718*4, 462*4, 974*4<br></td></tr
><tr
id=sl_svn23_400

><td class="source">	.dc.w	46*4, 558*4, 302*4, 814*4, 174*4, 686*4, 430*4, 942*4, 110*4, 622*4, 366*4, 878*4, 238*4, 750*4, 494*4, 1006*4<br></td></tr
><tr
id=sl_svn23_401

><td class="source">	.dc.w	30*4, 542*4, 286*4, 798*4, 158*4, 670*4, 414*4, 926*4, 94*4, 606*4, 350*4, 862*4, 222*4, 734*4, 478*4, 990*4<br></td></tr
><tr
id=sl_svn23_402

><td class="source">	.dc.w	62*4, 574*4, 318*4, 830*4, 190*4, 702*4, 446*4, 958*4, 126*4, 638*4, 382*4, 894*4, 254*4, 766*4, 510*4, 1022*4<br></td></tr
><tr
id=sl_svn23_403

><td class="source"><br></td></tr
><tr
id=sl_svn23_404

><td class="source">#elif FFT_N == 512<br></td></tr
><tr
id=sl_svn23_405

><td class="source">#ifdef INPUT_IQ<br></td></tr
><tr
id=sl_svn23_406

><td class="source">	.dc.w	1*4, 257*4, 129*4, 385*4, 65*4, 321*4, 193*4, 449*4, 33*4, 289*4, 161*4, 417*4, 97*4, 353*4, 225*4, 481*4<br></td></tr
><tr
id=sl_svn23_407

><td class="source">	.dc.w	17*4, 273*4, 145*4, 401*4, 81*4, 337*4, 209*4, 465*4, 49*4, 305*4, 177*4, 433*4, 113*4, 369*4, 241*4, 497*4<br></td></tr
><tr
id=sl_svn23_408

><td class="source">	.dc.w	9*4, 265*4, 137*4, 393*4, 73*4, 329*4, 201*4, 457*4, 41*4, 297*4, 169*4, 425*4, 105*4, 361*4, 233*4, 489*4<br></td></tr
><tr
id=sl_svn23_409

><td class="source">	.dc.w	25*4, 281*4, 153*4, 409*4, 89*4, 345*4, 217*4, 473*4, 57*4, 313*4, 185*4, 441*4, 121*4, 377*4, 249*4, 505*4<br></td></tr
><tr
id=sl_svn23_410

><td class="source">	.dc.w	5*4, 261*4, 133*4, 389*4, 69*4, 325*4, 197*4, 453*4, 37*4, 293*4, 165*4, 421*4, 101*4, 357*4, 229*4, 485*4<br></td></tr
><tr
id=sl_svn23_411

><td class="source">	.dc.w	21*4, 277*4, 149*4, 405*4, 85*4, 341*4, 213*4, 469*4, 53*4, 309*4, 181*4, 437*4, 117*4, 373*4, 245*4, 501*4<br></td></tr
><tr
id=sl_svn23_412

><td class="source">	.dc.w	13*4, 269*4, 141*4, 397*4, 77*4, 333*4, 205*4, 461*4, 45*4, 301*4, 173*4, 429*4, 109*4, 365*4, 237*4, 493*4<br></td></tr
><tr
id=sl_svn23_413

><td class="source">	.dc.w	29*4, 285*4, 157*4, 413*4, 93*4, 349*4, 221*4, 477*4, 61*4, 317*4, 189*4, 445*4, 125*4, 381*4, 253*4, 509*4<br></td></tr
><tr
id=sl_svn23_414

><td class="source">	.dc.w	3*4, 259*4, 131*4, 387*4, 67*4, 323*4, 195*4, 451*4, 35*4, 291*4, 163*4, 419*4, 99*4, 355*4, 227*4, 483*4<br></td></tr
><tr
id=sl_svn23_415

><td class="source">	.dc.w	19*4, 275*4, 147*4, 403*4, 83*4, 339*4, 211*4, 467*4, 51*4, 307*4, 179*4, 435*4, 115*4, 371*4, 243*4, 499*4<br></td></tr
><tr
id=sl_svn23_416

><td class="source">	.dc.w	11*4, 267*4, 139*4, 395*4, 75*4, 331*4, 203*4, 459*4, 43*4, 299*4, 171*4, 427*4, 107*4, 363*4, 235*4, 491*4<br></td></tr
><tr
id=sl_svn23_417

><td class="source">	.dc.w	27*4, 283*4, 155*4, 411*4, 91*4, 347*4, 219*4, 475*4, 59*4, 315*4, 187*4, 443*4, 123*4, 379*4, 251*4, 507*4<br></td></tr
><tr
id=sl_svn23_418

><td class="source">	.dc.w	7*4, 263*4, 135*4, 391*4, 71*4, 327*4, 199*4, 455*4, 39*4, 295*4, 167*4, 423*4, 103*4, 359*4, 231*4, 487*4<br></td></tr
><tr
id=sl_svn23_419

><td class="source">	.dc.w	23*4, 279*4, 151*4, 407*4, 87*4, 343*4, 215*4, 471*4, 55*4, 311*4, 183*4, 439*4, 119*4, 375*4, 247*4, 503*4<br></td></tr
><tr
id=sl_svn23_420

><td class="source">	.dc.w	15*4, 271*4, 143*4, 399*4, 79*4, 335*4, 207*4, 463*4, 47*4, 303*4, 175*4, 431*4, 111*4, 367*4, 239*4, 495*4<br></td></tr
><tr
id=sl_svn23_421

><td class="source">	.dc.w	31*4, 287*4, 159*4, 415*4, 95*4, 351*4, 223*4, 479*4, 63*4, 319*4, 191*4, 447*4, 127*4, 383*4, 255*4, 511*4<br></td></tr
><tr
id=sl_svn23_422

><td class="source">#endif<br></td></tr
><tr
id=sl_svn23_423

><td class="source">	.dc.w	0*4, 256*4, 128*4, 384*4, 64*4, 320*4, 192*4, 448*4, 32*4, 288*4, 160*4, 416*4, 96*4, 352*4, 224*4, 480*4<br></td></tr
><tr
id=sl_svn23_424

><td class="source">	.dc.w	16*4, 272*4, 144*4, 400*4, 80*4, 336*4, 208*4, 464*4, 48*4, 304*4, 176*4, 432*4, 112*4, 368*4, 240*4, 496*4<br></td></tr
><tr
id=sl_svn23_425

><td class="source">	.dc.w	8*4, 264*4, 136*4, 392*4, 72*4, 328*4, 200*4, 456*4, 40*4, 296*4, 168*4, 424*4, 104*4, 360*4, 232*4, 488*4<br></td></tr
><tr
id=sl_svn23_426

><td class="source">	.dc.w	24*4, 280*4, 152*4, 408*4, 88*4, 344*4, 216*4, 472*4, 56*4, 312*4, 184*4, 440*4, 120*4, 376*4, 248*4, 504*4<br></td></tr
><tr
id=sl_svn23_427

><td class="source">	.dc.w	4*4, 260*4, 132*4, 388*4, 68*4, 324*4, 196*4, 452*4, 36*4, 292*4, 164*4, 420*4, 100*4, 356*4, 228*4, 484*4<br></td></tr
><tr
id=sl_svn23_428

><td class="source">	.dc.w	20*4, 276*4, 148*4, 404*4, 84*4, 340*4, 212*4, 468*4, 52*4, 308*4, 180*4, 436*4, 116*4, 372*4, 244*4, 500*4<br></td></tr
><tr
id=sl_svn23_429

><td class="source">	.dc.w	12*4, 268*4, 140*4, 396*4, 76*4, 332*4, 204*4, 460*4, 44*4, 300*4, 172*4, 428*4, 108*4, 364*4, 236*4, 492*4<br></td></tr
><tr
id=sl_svn23_430

><td class="source">	.dc.w	28*4, 284*4, 156*4, 412*4, 92*4, 348*4, 220*4, 476*4, 60*4, 316*4, 188*4, 444*4, 124*4, 380*4, 252*4, 508*4<br></td></tr
><tr
id=sl_svn23_431

><td class="source">	.dc.w	2*4, 258*4, 130*4, 386*4, 66*4, 322*4, 194*4, 450*4, 34*4, 290*4, 162*4, 418*4, 98*4, 354*4, 226*4, 482*4<br></td></tr
><tr
id=sl_svn23_432

><td class="source">	.dc.w	18*4, 274*4, 146*4, 402*4, 82*4, 338*4, 210*4, 466*4, 50*4, 306*4, 178*4, 434*4, 114*4, 370*4, 242*4, 498*4<br></td></tr
><tr
id=sl_svn23_433

><td class="source">	.dc.w	10*4, 266*4, 138*4, 394*4, 74*4, 330*4, 202*4, 458*4, 42*4, 298*4, 170*4, 426*4, 106*4, 362*4, 234*4, 490*4<br></td></tr
><tr
id=sl_svn23_434

><td class="source">	.dc.w	26*4, 282*4, 154*4, 410*4, 90*4, 346*4, 218*4, 474*4, 58*4, 314*4, 186*4, 442*4, 122*4, 378*4, 250*4, 506*4<br></td></tr
><tr
id=sl_svn23_435

><td class="source">	.dc.w	6*4, 262*4, 134*4, 390*4, 70*4, 326*4, 198*4, 454*4, 38*4, 294*4, 166*4, 422*4, 102*4, 358*4, 230*4, 486*4<br></td></tr
><tr
id=sl_svn23_436

><td class="source">	.dc.w	22*4, 278*4, 150*4, 406*4, 86*4, 342*4, 214*4, 470*4, 54*4, 310*4, 182*4, 438*4, 118*4, 374*4, 246*4, 502*4<br></td></tr
><tr
id=sl_svn23_437

><td class="source">	.dc.w	14*4, 270*4, 142*4, 398*4, 78*4, 334*4, 206*4, 462*4, 46*4, 302*4, 174*4, 430*4, 110*4, 366*4, 238*4, 494*4<br></td></tr
><tr
id=sl_svn23_438

><td class="source">	.dc.w	30*4, 286*4, 158*4, 414*4, 94*4, 350*4, 222*4, 478*4, 62*4, 318*4, 190*4, 446*4, 126*4, 382*4, 254*4, 510*4<br></td></tr
><tr
id=sl_svn23_439

><td class="source"><br></td></tr
><tr
id=sl_svn23_440

><td class="source">#elif FFT_N == 256<br></td></tr
><tr
id=sl_svn23_441

><td class="source">#ifdef INPUT_IQ<br></td></tr
><tr
id=sl_svn23_442

><td class="source">	.dc.w	1*4, 129*4, 65*4, 193*4, 33*4, 161*4, 97*4, 225*4, 17*4, 145*4, 81*4, 209*4, 49*4, 177*4, 113*4, 241*4<br></td></tr
><tr
id=sl_svn23_443

><td class="source">	.dc.w	9*4, 137*4, 73*4, 201*4, 41*4, 169*4, 105*4, 233*4, 25*4, 153*4, 89*4, 217*4, 57*4, 185*4, 121*4, 249*4<br></td></tr
><tr
id=sl_svn23_444

><td class="source">	.dc.w	5*4, 133*4, 69*4, 197*4, 37*4, 165*4, 101*4, 229*4, 21*4, 149*4, 85*4, 213*4, 53*4, 181*4, 117*4, 245*4<br></td></tr
><tr
id=sl_svn23_445

><td class="source">	.dc.w	13*4, 141*4, 77*4, 205*4, 45*4, 173*4, 109*4, 237*4, 29*4, 157*4, 93*4, 221*4, 61*4, 189*4, 125*4, 253*4<br></td></tr
><tr
id=sl_svn23_446

><td class="source">	.dc.w	3*4, 131*4, 67*4, 195*4, 35*4, 163*4, 99*4, 227*4, 19*4, 147*4, 83*4, 211*4, 51*4, 179*4, 115*4, 243*4<br></td></tr
><tr
id=sl_svn23_447

><td class="source">	.dc.w	11*4, 139*4, 75*4, 203*4, 43*4, 171*4, 107*4, 235*4, 27*4, 155*4, 91*4, 219*4, 59*4, 187*4, 123*4, 251*4<br></td></tr
><tr
id=sl_svn23_448

><td class="source">	.dc.w	7*4, 135*4, 71*4, 199*4, 39*4, 167*4, 103*4, 231*4, 23*4, 151*4, 87*4, 215*4, 55*4, 183*4, 119*4, 247*4<br></td></tr
><tr
id=sl_svn23_449

><td class="source">	.dc.w	15*4, 143*4, 79*4, 207*4, 47*4, 175*4, 111*4, 239*4, 31*4, 159*4, 95*4, 223*4, 63*4, 191*4, 127*4, 255*4<br></td></tr
><tr
id=sl_svn23_450

><td class="source">#endif<br></td></tr
><tr
id=sl_svn23_451

><td class="source">	.dc.w	0*4, 128*4, 64*4, 192*4, 32*4, 160*4, 96*4, 224*4, 16*4, 144*4, 80*4, 208*4, 48*4, 176*4, 112*4, 240*4<br></td></tr
><tr
id=sl_svn23_452

><td class="source">	.dc.w	8*4, 136*4, 72*4, 200*4, 40*4, 168*4, 104*4, 232*4, 24*4, 152*4, 88*4, 216*4, 56*4, 184*4, 120*4, 248*4<br></td></tr
><tr
id=sl_svn23_453

><td class="source">	.dc.w	4*4, 132*4, 68*4, 196*4, 36*4, 164*4, 100*4, 228*4, 20*4, 148*4, 84*4, 212*4, 52*4, 180*4, 116*4, 244*4<br></td></tr
><tr
id=sl_svn23_454

><td class="source">	.dc.w	12*4, 140*4, 76*4, 204*4, 44*4, 172*4, 108*4, 236*4, 28*4, 156*4, 92*4, 220*4, 60*4, 188*4, 124*4, 252*4<br></td></tr
><tr
id=sl_svn23_455

><td class="source">	.dc.w	2*4, 130*4, 66*4, 194*4, 34*4, 162*4, 98*4, 226*4, 18*4, 146*4, 82*4, 210*4, 50*4, 178*4, 114*4, 242*4<br></td></tr
><tr
id=sl_svn23_456

><td class="source">	.dc.w	10*4, 138*4, 74*4, 202*4, 42*4, 170*4, 106*4, 234*4, 26*4, 154*4, 90*4, 218*4, 58*4, 186*4, 122*4, 250*4<br></td></tr
><tr
id=sl_svn23_457

><td class="source">	.dc.w	6*4, 134*4, 70*4, 198*4, 38*4, 166*4, 102*4, 230*4, 22*4, 150*4, 86*4, 214*4, 54*4, 182*4, 118*4, 246*4<br></td></tr
><tr
id=sl_svn23_458

><td class="source">	.dc.w	14*4, 142*4, 78*4, 206*4, 46*4, 174*4, 110*4, 238*4, 30*4, 158*4, 94*4, 222*4, 62*4, 190*4, 126*4, 254*4<br></td></tr
><tr
id=sl_svn23_459

><td class="source"><br></td></tr
><tr
id=sl_svn23_460

><td class="source">#elif FFT_N == 128<br></td></tr
><tr
id=sl_svn23_461

><td class="source">#ifdef INPUT_IQ<br></td></tr
><tr
id=sl_svn23_462

><td class="source">	.dc.w	1*4, 65*4, 33*4, 97*4, 17*4, 81*4, 49*4, 113*4, 9*4, 73*4, 41*4, 105*4, 25*4, 89*4, 57*4, 121*4<br></td></tr
><tr
id=sl_svn23_463

><td class="source">	.dc.w	5*4, 69*4, 37*4, 101*4, 21*4, 85*4, 53*4, 117*4, 13*4, 77*4, 45*4, 109*4, 29*4, 93*4, 61*4, 125*4<br></td></tr
><tr
id=sl_svn23_464

><td class="source">	.dc.w	3*4, 67*4, 35*4, 99*4, 19*4, 83*4, 51*4, 115*4, 11*4, 75*4, 43*4, 107*4, 27*4, 91*4, 59*4, 123*4<br></td></tr
><tr
id=sl_svn23_465

><td class="source">	.dc.w	7*4, 71*4, 39*4, 103*4, 23*4, 87*4, 55*4, 119*4, 15*4, 79*4, 47*4, 111*4, 31*4, 95*4, 63*4, 127*4<br></td></tr
><tr
id=sl_svn23_466

><td class="source">#endif<br></td></tr
><tr
id=sl_svn23_467

><td class="source">	.dc.w	0*4, 64*4, 32*4, 96*4, 16*4, 80*4, 48*4, 112*4, 8*4, 72*4, 40*4, 104*4, 24*4, 88*4, 56*4, 120*4<br></td></tr
><tr
id=sl_svn23_468

><td class="source">	.dc.w	4*4, 68*4, 36*4, 100*4, 20*4, 84*4, 52*4, 116*4, 12*4, 76*4, 44*4, 108*4, 28*4, 92*4, 60*4, 124*4<br></td></tr
><tr
id=sl_svn23_469

><td class="source">	.dc.w	2*4, 66*4, 34*4, 98*4, 18*4, 82*4, 50*4, 114*4, 10*4, 74*4, 42*4, 106*4, 26*4, 90*4, 58*4, 122*4<br></td></tr
><tr
id=sl_svn23_470

><td class="source">	.dc.w	6*4, 70*4, 38*4, 102*4, 22*4, 86*4, 54*4, 118*4, 14*4, 78*4, 46*4, 110*4, 30*4, 94*4, 62*4, 126*4<br></td></tr
><tr
id=sl_svn23_471

><td class="source"><br></td></tr
><tr
id=sl_svn23_472

><td class="source">#elif FFT_N == 64<br></td></tr
><tr
id=sl_svn23_473

><td class="source">#ifdef INPUT_IQ<br></td></tr
><tr
id=sl_svn23_474

><td class="source">	.dc.w	1*4, 33*4, 17*4, 49*4, 9*4, 41*4, 25*4, 57*4, 5*4, 37*4, 21*4, 53*4, 13*4, 45*4, 29*4, 61*4<br></td></tr
><tr
id=sl_svn23_475

><td class="source">	.dc.w	3*4, 35*4, 19*4, 51*4, 11*4, 43*4, 27*4, 59*4, 7*4, 39*4, 23*4, 55*4, 15*4, 47*4, 31*4, 63*4<br></td></tr
><tr
id=sl_svn23_476

><td class="source">#endif<br></td></tr
><tr
id=sl_svn23_477

><td class="source">	.dc.w	0*4, 32*4, 16*4, 48*4, 8*4, 40*4, 24*4, 56*4, 4*4, 36*4, 20*4, 52*4, 12*4, 44*4, 28*4, 60*4<br></td></tr
><tr
id=sl_svn23_478

><td class="source">	.dc.w	2*4, 34*4, 18*4, 50*4, 10*4, 42*4, 26*4, 58*4, 6*4, 38*4, 22*4, 54*4, 14*4, 46*4, 30*4, 62*4<br></td></tr
><tr
id=sl_svn23_479

><td class="source">#endif<br></td></tr
><tr
id=sl_svn23_480

><td class="source"><br></td></tr
><tr
id=sl_svn23_481

><td class="source"><br></td></tr
><tr
id=sl_svn23_482

><td class="source"><br></td></tr
><tr
id=sl_svn23_483

><td class="source">;----------------------------------------------------------------------------;<br></td></tr
><tr
id=sl_svn23_484

><td class="source">#ifndef INPUT_NOUSE<br></td></tr
><tr
id=sl_svn23_485

><td class="source">.global fft_input<br></td></tr
><tr
id=sl_svn23_486

><td class="source">.func fft_input<br></td></tr
><tr
id=sl_svn23_487

><td class="source">fft_input:<br></td></tr
><tr
id=sl_svn23_488

><td class="source">	pushw	T2H,T2L<br></td></tr
><tr
id=sl_svn23_489

><td class="source">	pushw	AH,AL<br></td></tr
><tr
id=sl_svn23_490

><td class="source">	pushw	YH,YL<br></td></tr
><tr
id=sl_svn23_491

><td class="source"><br></td></tr
><tr
id=sl_svn23_492

><td class="source">	movw	XL, EL				;X = array_src;<br></td></tr
><tr
id=sl_svn23_493

><td class="source">	movw	YL, DL				;Y = array_bfly;<br></td></tr
><tr
id=sl_svn23_494

><td class="source">	clr	EH				;Zero<br></td></tr
><tr
id=sl_svn23_495

><td class="source">	ldiw	ZH,ZL, tbl_window		;Z = &amp;tbl_window[0];<br></td></tr
><tr
id=sl_svn23_496

><td class="source">	ldiw	AH,AL, FFT_N			;A = FFT_N;<br></td></tr
><tr
id=sl_svn23_497

><td class="source">1:	lpmw	BH,BL, Z+			;B = *Z++; (window)<br></td></tr
><tr
id=sl_svn23_498

><td class="source">	ldw	CH,CL, X+			;C = *X++; (I-axis)<br></td></tr
><tr
id=sl_svn23_499

><td class="source">	FMULS16	DH,DL,T2H,T2L, BH,BL, CH,CL	;D = B * C;<br></td></tr
><tr
id=sl_svn23_500

><td class="source">	stw	Y+, DH,DL			;*Y++ = D;<br></td></tr
><tr
id=sl_svn23_501

><td class="source">#ifdef INPUT_IQ<br></td></tr
><tr
id=sl_svn23_502

><td class="source">	ldw	CH,CL, X+			;C = *X++; (Q-axis)<br></td></tr
><tr
id=sl_svn23_503

><td class="source">	FMULS16	DH,DL,T2H,T2L, BH,BL, CH,CL	;D = B * C;<br></td></tr
><tr
id=sl_svn23_504

><td class="source">#endif<br></td></tr
><tr
id=sl_svn23_505

><td class="source">	stw	Y+, DH,DL			;*Y++ = D;<br></td></tr
><tr
id=sl_svn23_506

><td class="source">	subiw	AH,AL, 1			;while(--A)<br></td></tr
><tr
id=sl_svn23_507

><td class="source">	brne	1b				;/<br></td></tr
><tr
id=sl_svn23_508

><td class="source"><br></td></tr
><tr
id=sl_svn23_509

><td class="source">	popw	YH,YL<br></td></tr
><tr
id=sl_svn23_510

><td class="source">	popw	AH,AL<br></td></tr
><tr
id=sl_svn23_511

><td class="source">	popw	T2H,T2L<br></td></tr
><tr
id=sl_svn23_512

><td class="source">	clr	r1<br></td></tr
><tr
id=sl_svn23_513

><td class="source">	ret<br></td></tr
><tr
id=sl_svn23_514

><td class="source">.endfunc<br></td></tr
><tr
id=sl_svn23_515

><td class="source">#endif	/* INPUT_NOUSE */<br></td></tr
><tr
id=sl_svn23_516

><td class="source"><br></td></tr
><tr
id=sl_svn23_517

><td class="source"><br></td></tr
><tr
id=sl_svn23_518

><td class="source"><br></td></tr
><tr
id=sl_svn23_519

><td class="source">;----------------------------------------------------------------------------;<br></td></tr
><tr
id=sl_svn23_520

><td class="source">.global fft_execute<br></td></tr
><tr
id=sl_svn23_521

><td class="source">.func fft_execute<br></td></tr
><tr
id=sl_svn23_522

><td class="source">fft_execute:<br></td></tr
><tr
id=sl_svn23_523

><td class="source">	pushw	T2H,T2L<br></td></tr
><tr
id=sl_svn23_524

><td class="source">	pushw	T4H,T4L<br></td></tr
><tr
id=sl_svn23_525

><td class="source">	pushw	T6H,T6L<br></td></tr
><tr
id=sl_svn23_526

><td class="source">	pushw	T8H,T8L<br></td></tr
><tr
id=sl_svn23_527

><td class="source">	pushw	T10H,T10L<br></td></tr
><tr
id=sl_svn23_528

><td class="source">	pushw	T12H,T12L<br></td></tr
><tr
id=sl_svn23_529

><td class="source">	pushw	T14H,T14L<br></td></tr
><tr
id=sl_svn23_530

><td class="source">	pushw	AH,AL<br></td></tr
><tr
id=sl_svn23_531

><td class="source">	pushw	YH,YL<br></td></tr
><tr
id=sl_svn23_532

><td class="source"><br></td></tr
><tr
id=sl_svn23_533

><td class="source">	movw	ZL, EL				;Z = array_bfly;<br></td></tr
><tr
id=sl_svn23_534

><td class="source">	ldiw	EH,EL, 1			;E = 1;<br></td></tr
><tr
id=sl_svn23_535

><td class="source">	ldiw	XH,XL, FFT_N/2			;X = FFT_N/2;<br></td></tr
><tr
id=sl_svn23_536

><td class="source">1:	ldi	AL, 4				;T12 = E; (angular speed)<br></td></tr
><tr
id=sl_svn23_537

><td class="source">	mul	EL, AL				;<br></td></tr
><tr
id=sl_svn23_538

><td class="source">	movw	T12L, T0L			;<br></td></tr
><tr
id=sl_svn23_539

><td class="source">	mul	EH, AL				;<br></td></tr
><tr
id=sl_svn23_540

><td class="source">	add	T12H, T0L			;/<br></td></tr
><tr
id=sl_svn23_541

><td class="source">	movw	T14L, EL			;T14 = E;<br></td></tr
><tr
id=sl_svn23_542

><td class="source">	pushw	EH,EL<br></td></tr
><tr
id=sl_svn23_543

><td class="source">	movw	YL, ZL				;Z = &amp;array_bfly[0];<br></td></tr
><tr
id=sl_svn23_544

><td class="source">	mul	XL, AL				;Y = &amp;array_bfly[X];<br></td></tr
><tr
id=sl_svn23_545

><td class="source">	addw	YH,YL, T0H,T0L			;<br></td></tr
><tr
id=sl_svn23_546

><td class="source">	mul	XH, AL				;<br></td></tr
><tr
id=sl_svn23_547

><td class="source">	add	YH, T0L				;/<br></td></tr
><tr
id=sl_svn23_548

><td class="source">	pushw	ZH,ZL<br></td></tr
><tr
id=sl_svn23_549

><td class="source">2:	clrw	T10H,T10L			;T10 = 0 (angle)<br></td></tr
><tr
id=sl_svn23_550

><td class="source">	clr	EH				;Zero reg.<br></td></tr
><tr
id=sl_svn23_551

><td class="source">3:	lddw	AH,AL, Z+0			;A = *Z - *Y; *Z++ += *Y;<br></td></tr
><tr
id=sl_svn23_552

><td class="source">	asrw	AH,AL				;<br></td></tr
><tr
id=sl_svn23_553

><td class="source">	lddw	DH,DL, Y+0			;<br></td></tr
><tr
id=sl_svn23_554

><td class="source">	asrw	DH,DL				;<br></td></tr
><tr
id=sl_svn23_555

><td class="source">	movw	CL, AL				;<br></td></tr
><tr
id=sl_svn23_556

><td class="source">	subw	AH,AL, DH,DL			;<br></td></tr
><tr
id=sl_svn23_557

><td class="source">	addw	CH,CL, DH,DL			;<br></td></tr
><tr
id=sl_svn23_558

><td class="source">	stw	Z+, CH,CL			;/<br></td></tr
><tr
id=sl_svn23_559

><td class="source">	lddw	BH,BL, Z+0			;B = *Z - *Y; *Z++ += *Y;<br></td></tr
><tr
id=sl_svn23_560

><td class="source">	asrw	BH,BL				;<br></td></tr
><tr
id=sl_svn23_561

><td class="source">	lddw	DH,DL, Y+2			;<br></td></tr
><tr
id=sl_svn23_562

><td class="source">	asrw	DH,DL				;<br></td></tr
><tr
id=sl_svn23_563

><td class="source">	movw	CL, BL				;<br></td></tr
><tr
id=sl_svn23_564

><td class="source">	subw	BH,BL, DH,DL			;<br></td></tr
><tr
id=sl_svn23_565

><td class="source">	addw	CH,CL, DH,DL			;<br></td></tr
><tr
id=sl_svn23_566

><td class="source">	stw	Z+, CH,CL			;/<br></td></tr
><tr
id=sl_svn23_567

><td class="source">	movw	T0L, ZL<br></td></tr
><tr
id=sl_svn23_568

><td class="source">	ldiw	ZH,ZL, tbl_cos_sin		;C = cos(T10); D = sin(T10);<br></td></tr
><tr
id=sl_svn23_569

><td class="source">	addw	ZH,ZL, T10H,T10L		;<br></td></tr
><tr
id=sl_svn23_570

><td class="source">	lpmw	CH,CL, Z+			;<br></td></tr
><tr
id=sl_svn23_571

><td class="source">	lpmw	DH,DL, Z+			;/<br></td></tr
><tr
id=sl_svn23_572

><td class="source">	movw	ZL, T0L<br></td></tr
><tr
id=sl_svn23_573

><td class="source">	FMULS16	T4H,T4L,T2H,T2L, AH,AL, CH,CL	;*Y++ = A * C + B * D;<br></td></tr
><tr
id=sl_svn23_574

><td class="source">	FMULS16	T8H,T8L,T6H,T6L, BH,BL, DH,DL	;<br></td></tr
><tr
id=sl_svn23_575

><td class="source">	addd	T4H,T4L,T2H,T2L, T8H,T8L,T6H,T6L;<br></td></tr
><tr
id=sl_svn23_576

><td class="source">	stw	Y+, T4H,T4L			;/<br></td></tr
><tr
id=sl_svn23_577

><td class="source">	FMULS16	T4H,T4L,T2H,T2L, BH,BL, CH,CL 	;*Y++ = B * C - A * D;<br></td></tr
><tr
id=sl_svn23_578

><td class="source">	FMULS16	T8H,T8L,T6H,T6L, AH,AL, DH,DL 	;<br></td></tr
><tr
id=sl_svn23_579

><td class="source">	subd	T4H,T4L,T2H,T2L, T8H,T8L,T6H,T6L;<br></td></tr
><tr
id=sl_svn23_580

><td class="source">	stw	Y+, T4H,T4L			;/<br></td></tr
><tr
id=sl_svn23_581

><td class="source">	addw	T10H,T10L, T12H,T12L		;T10 += T12; (next angle)<br></td></tr
><tr
id=sl_svn23_582

><td class="source">#if FFT_N &gt;= 128<br></td></tr
><tr
id=sl_svn23_583

><td class="source">	sbrs	T10H, FFT_B - 7			;while(T10 &lt; pi)<br></td></tr
><tr
id=sl_svn23_584

><td class="source">#else<br></td></tr
><tr
id=sl_svn23_585

><td class="source">	sbrs	T10L, FFT_B + 1<br></td></tr
><tr
id=sl_svn23_586

><td class="source">#endif<br></td></tr
><tr
id=sl_svn23_587

><td class="source">	rjmp	3b				;/<br></td></tr
><tr
id=sl_svn23_588

><td class="source">	ldi	AL, 4				;Y += X; Z += X; (skip split segment)<br></td></tr
><tr
id=sl_svn23_589

><td class="source">	mul	XL, AL<br></td></tr
><tr
id=sl_svn23_590

><td class="source">	addw	YH,YL, T0H,T0L			;<br></td></tr
><tr
id=sl_svn23_591

><td class="source">	addw	ZH,ZL, T0H,T0L			;<br></td></tr
><tr
id=sl_svn23_592

><td class="source">	mul	XH, AL				;<br></td></tr
><tr
id=sl_svn23_593

><td class="source">	add	YH, T0L				;<br></td></tr
><tr
id=sl_svn23_594

><td class="source">	add	ZH, T0L				;/<br></td></tr
><tr
id=sl_svn23_595

><td class="source">	ldi	EL, 1				;while(--T14)<br></td></tr
><tr
id=sl_svn23_596

><td class="source">	subw	T14H,T14L, EH,EL		;<br></td></tr
><tr
id=sl_svn23_597

><td class="source">	rjne	2b				;/<br></td></tr
><tr
id=sl_svn23_598

><td class="source">	popw	ZH,ZL<br></td></tr
><tr
id=sl_svn23_599

><td class="source">	popw	EH,EL<br></td></tr
><tr
id=sl_svn23_600

><td class="source">	lslw	EH,EL				;E *= 2;<br></td></tr
><tr
id=sl_svn23_601

><td class="source">	lsrw	XH,XL				;while(X /= 2)<br></td></tr
><tr
id=sl_svn23_602

><td class="source">	adiw	XL, 0				;<br></td></tr
><tr
id=sl_svn23_603

><td class="source">	rjne	1b				;/<br></td></tr
><tr
id=sl_svn23_604

><td class="source"><br></td></tr
><tr
id=sl_svn23_605

><td class="source">	popw	YH,YL<br></td></tr
><tr
id=sl_svn23_606

><td class="source">	popw	AH,AL<br></td></tr
><tr
id=sl_svn23_607

><td class="source">	popw	T14H,T14L<br></td></tr
><tr
id=sl_svn23_608

><td class="source">	popw	T12H,T12L<br></td></tr
><tr
id=sl_svn23_609

><td class="source">	popw	T10H,T10L<br></td></tr
><tr
id=sl_svn23_610

><td class="source">	popw	T8H,T8L<br></td></tr
><tr
id=sl_svn23_611

><td class="source">	popw	T6H,T6L<br></td></tr
><tr
id=sl_svn23_612

><td class="source">	popw	T4H,T4L<br></td></tr
><tr
id=sl_svn23_613

><td class="source">	popw	T2H,T2L<br></td></tr
><tr
id=sl_svn23_614

><td class="source">;	clr	r1<br></td></tr
><tr
id=sl_svn23_615

><td class="source">	ret<br></td></tr
><tr
id=sl_svn23_616

><td class="source">.endfunc<br></td></tr
><tr
id=sl_svn23_617

><td class="source"><br></td></tr
><tr
id=sl_svn23_618

><td class="source"><br></td></tr
><tr
id=sl_svn23_619

><td class="source"><br></td></tr
><tr
id=sl_svn23_620

><td class="source">;----------------------------------------------------------------------------;<br></td></tr
><tr
id=sl_svn23_621

><td class="source">.global fft_output<br></td></tr
><tr
id=sl_svn23_622

><td class="source">.func fft_output<br></td></tr
><tr
id=sl_svn23_623

><td class="source">fft_output:<br></td></tr
><tr
id=sl_svn23_624

><td class="source">	pushw	T2H,T2L<br></td></tr
><tr
id=sl_svn23_625

><td class="source">	pushw	T4H,T4L<br></td></tr
><tr
id=sl_svn23_626

><td class="source">	pushw	T6H,T6L<br></td></tr
><tr
id=sl_svn23_627

><td class="source">	pushw	T8H,T8L<br></td></tr
><tr
id=sl_svn23_628

><td class="source">	pushw	T10H,T10L<br></td></tr
><tr
id=sl_svn23_629

><td class="source">	pushw	AH,AL<br></td></tr
><tr
id=sl_svn23_630

><td class="source">	pushw	YH,YL<br></td></tr
><tr
id=sl_svn23_631

><td class="source"><br></td></tr
><tr
id=sl_svn23_632

><td class="source">	movw	T10L, EL			;T10 = array_bfly;<br></td></tr
><tr
id=sl_svn23_633

><td class="source">	movw	YL, DL				;Y = array_output;<br></td></tr
><tr
id=sl_svn23_634

><td class="source">	ldiw	ZH,ZL, tbl_bitrev		;Z = tbl_bitrev;<br></td></tr
><tr
id=sl_svn23_635

><td class="source">	clr	EH				;Zero<br></td></tr
><tr
id=sl_svn23_636

><td class="source">#ifdef INPUT_IQ<br></td></tr
><tr
id=sl_svn23_637

><td class="source">	ldiw	AH,AL, FFT_N			;A = FFT_N; (plus/minus)<br></td></tr
><tr
id=sl_svn23_638

><td class="source">#else<br></td></tr
><tr
id=sl_svn23_639

><td class="source">	ldiw	AH,AL, FFT_N / 2		;A = FFT_N / 2; (plus only)<br></td></tr
><tr
id=sl_svn23_640

><td class="source">#endif<br></td></tr
><tr
id=sl_svn23_641

><td class="source">1:	lpmw	XH,XL, Z+			;X = *Z++;<br></td></tr
><tr
id=sl_svn23_642

><td class="source">	addw	XH,XL, T10H,T10L		;X += array_bfly;<br></td></tr
><tr
id=sl_svn23_643

><td class="source">	ldw	BH,BL, X+			;B = *X++;<br></td></tr
><tr
id=sl_svn23_644

><td class="source">	ldw	CH,CL, X+			;C = *X++;<br></td></tr
><tr
id=sl_svn23_645

><td class="source">	FMULS16	T4H,T4L,T2H,T2L, BH,BL, BH,BL	;T4:T2 = B * B;<br></td></tr
><tr
id=sl_svn23_646

><td class="source">	FMULS16	T8H,T8L,T6H,T6L, CH,CL, CH,CL	;T8:T6 = C * C;<br></td></tr
><tr
id=sl_svn23_647

><td class="source">	addd	T4H,T4L,T2H,T2L, T8H,T8L,T6H,T6L;T4:T2 += T8:T6;<br></td></tr
><tr
id=sl_svn23_648

><td class="source">	SQRT32					;B = sqrt(T4:T2);<br></td></tr
><tr
id=sl_svn23_649

><td class="source">	stw	Y+, BH,BL			;*Y++ = B;<br></td></tr
><tr
id=sl_svn23_650

><td class="source">	subiw	AH,AL, 1			;while(--A)<br></td></tr
><tr
id=sl_svn23_651

><td class="source">	rjne	1b				;/<br></td></tr
><tr
id=sl_svn23_652

><td class="source"><br></td></tr
><tr
id=sl_svn23_653

><td class="source">	popw	YH,YL<br></td></tr
><tr
id=sl_svn23_654

><td class="source">	popw	AH,AL<br></td></tr
><tr
id=sl_svn23_655

><td class="source">	popw	T10H,T10L<br></td></tr
><tr
id=sl_svn23_656

><td class="source">	popw	T8H,T8L<br></td></tr
><tr
id=sl_svn23_657

><td class="source">	popw	T6H,T6L<br></td></tr
><tr
id=sl_svn23_658

><td class="source">	popw	T4H,T4L<br></td></tr
><tr
id=sl_svn23_659

><td class="source">	popw	T2H,T2L<br></td></tr
><tr
id=sl_svn23_660

><td class="source">	clr	r1<br></td></tr
><tr
id=sl_svn23_661

><td class="source">	ret<br></td></tr
><tr
id=sl_svn23_662

><td class="source">.endfunc<br></td></tr
><tr
id=sl_svn23_663

><td class="source"><br></td></tr
><tr
id=sl_svn23_664

><td class="source"><br></td></tr
><tr
id=sl_svn23_665

><td class="source"><br></td></tr
><tr
id=sl_svn23_666

><td class="source">;----------------------------------------------------------------------------;<br></td></tr
><tr
id=sl_svn23_667

><td class="source">.global fmuls_f<br></td></tr
><tr
id=sl_svn23_668

><td class="source">.func fmuls_f<br></td></tr
><tr
id=sl_svn23_669

><td class="source">fmuls_f:<br></td></tr
><tr
id=sl_svn23_670

><td class="source">	movw	CL, EL				;C = E;<br></td></tr
><tr
id=sl_svn23_671

><td class="source">	clr	EH	;Zero<br></td></tr
><tr
id=sl_svn23_672

><td class="source">	FMULS16	ZH,ZL,XH,XL, CH,CL, DH,DL	;Z:X = C * D;<br></td></tr
><tr
id=sl_svn23_673

><td class="source">	movw	EL, ZL<br></td></tr
><tr
id=sl_svn23_674

><td class="source">	clr	r1<br></td></tr
><tr
id=sl_svn23_675

><td class="source">	ret<br></td></tr
><tr
id=sl_svn23_676

><td class="source">.endfunc<br></td></tr
><tr
id=sl_svn23_677

><td class="source"><br></td></tr
></table></pre>
<pre><table width="100%"><tr class="cursor_stop cursor_hidden"><td></td></tr></table></pre>
</td>
</tr></table>

 
<script type="text/javascript">
 var lineNumUnderMouse = -1;
 
 function gutterOver(num) {
 gutterOut();
 var newTR = document.getElementById('gr_svn23_' + num);
 if (newTR) {
 newTR.className = 'undermouse';
 }
 lineNumUnderMouse = num;
 }
 function gutterOut() {
 if (lineNumUnderMouse != -1) {
 var oldTR = document.getElementById(
 'gr_svn23_' + lineNumUnderMouse);
 if (oldTR) {
 oldTR.className = '';
 }
 lineNumUnderMouse = -1;
 }
 }
 var numsGenState = {table_base_id: 'nums_table_'};
 var srcGenState = {table_base_id: 'src_table_'};
 var alignerRunning = false;
 var startOver = false;
 function setLineNumberHeights() {
 if (alignerRunning) {
 startOver = true;
 return;
 }
 numsGenState.chunk_id = 0;
 numsGenState.table = document.getElementById('nums_table_0');
 numsGenState.row_num = 0;
 if (!numsGenState.table) {
 return; // Silently exit if no file is present.
 }
 srcGenState.chunk_id = 0;
 srcGenState.table = document.getElementById('src_table_0');
 srcGenState.row_num = 0;
 alignerRunning = true;
 continueToSetLineNumberHeights();
 }
 function rowGenerator(genState) {
 if (genState.row_num < genState.table.rows.length) {
 var currentRow = genState.table.rows[genState.row_num];
 genState.row_num++;
 return currentRow;
 }
 var newTable = document.getElementById(
 genState.table_base_id + (genState.chunk_id + 1));
 if (newTable) {
 genState.chunk_id++;
 genState.row_num = 0;
 genState.table = newTable;
 return genState.table.rows[0];
 }
 return null;
 }
 var MAX_ROWS_PER_PASS = 1000;
 function continueToSetLineNumberHeights() {
 var rowsInThisPass = 0;
 var numRow = 1;
 var srcRow = 1;
 while (numRow && srcRow && rowsInThisPass < MAX_ROWS_PER_PASS) {
 numRow = rowGenerator(numsGenState);
 srcRow = rowGenerator(srcGenState);
 rowsInThisPass++;
 if (numRow && srcRow) {
 if (numRow.offsetHeight != srcRow.offsetHeight) {
 numRow.firstChild.style.height = srcRow.offsetHeight + 'px';
 }
 }
 }
 if (rowsInThisPass >= MAX_ROWS_PER_PASS) {
 setTimeout(continueToSetLineNumberHeights, 10);
 } else {
 alignerRunning = false;
 if (startOver) {
 startOver = false;
 setTimeout(setLineNumberHeights, 500);
 }
 }
 }
 function initLineNumberHeights() {
 // Do 2 complete passes, because there can be races
 // between this code and prettify.
 startOver = true;
 setTimeout(setLineNumberHeights, 250);
 window.onresize = setLineNumberHeights;
 }
 initLineNumberHeights();
</script>

 
 
 <div id="log">
 <div style="text-align:right">
 <a class="ifCollapse" href="#" onclick="_toggleMeta(this); return false">Show details</a>
 <a class="ifExpand" href="#" onclick="_toggleMeta(this); return false">Hide details</a>
 </div>
 <div class="ifExpand">
 
 
 <div class="pmeta_bubble_bg" style="border:1px solid white">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <div id="changelog">
 <p>Change log</p>
 <div>
 <a href="/p/neuroelec/source/detail?spec=svn23&amp;r=21">r21</a>
 by neurostar
 on Oct 26, 2011
 &nbsp; <a href="/p/neuroelec/source/diff?spec=svn23&r=21&amp;format=side&amp;path=/trunk/libraries/Arduino+1.0/ffft/ffft.S&amp;old_path=/trunk/libraries/Arduino+1.0/ffft/ffft.S&amp;old=">Diff</a>
 </div>
 <pre>add Arduino 1.0 compatible lib and re-
organize svn</pre>
 </div>
 
 
 
 
 
 
 <script type="text/javascript">
 var detail_url = '/p/neuroelec/source/detail?r=21&spec=svn23';
 var publish_url = '/p/neuroelec/source/detail?r=21&spec=svn23#publish';
 // describe the paths of this revision in javascript.
 var changed_paths = [];
 var changed_urls = [];
 
 changed_paths.push('/trunk/Demo_Projects');
 changed_urls.push('/p/neuroelec/source/browse/trunk/Demo_Projects?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/Demo_Projects/LEDColorPicker');
 changed_urls.push('/p/neuroelec/source/browse/trunk/Demo_Projects/LEDColorPicker?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/Demo_Projects/LEDColorPicker/LEDColorPicker.pde');
 changed_urls.push('/p/neuroelec/source/browse/trunk/Demo_Projects/LEDColorPicker/LEDColorPicker.pde?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/Demo_Projects/Python-ColorPicker');
 changed_urls.push('/p/neuroelec/source/browse/trunk/Demo_Projects/Python-ColorPicker?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/Demo_Projects/Python-ColorPicker/Python-ColorPicker.pde');
 changed_urls.push('/p/neuroelec/source/browse/trunk/Demo_Projects/Python-ColorPicker/Python-ColorPicker.pde?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/Demo_Projects/Python-ColorPicker/Python-code');
 changed_urls.push('/p/neuroelec/source/browse/trunk/Demo_Projects/Python-ColorPicker/Python-code?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/Demo_Projects/Python-ColorPicker/Python-code/arduino-rgb.py');
 changed_urls.push('/p/neuroelec/source/browse/trunk/Demo_Projects/Python-ColorPicker/Python-code/arduino-rgb.py?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/Demo_Projects/Python-ColorPicker/Python-code/gtk-color-picker.py');
 changed_urls.push('/p/neuroelec/source/browse/trunk/Demo_Projects/Python-ColorPicker/Python-code/gtk-color-picker.py?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/Demo_Projects/Python-ColorPicker/Python-code/hsv.py');
 changed_urls.push('/p/neuroelec/source/browse/trunk/Demo_Projects/Python-ColorPicker/Python-code/hsv.py?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/Demo_Projects/Python-ColorPicker/Python-code/rgb.py');
 changed_urls.push('/p/neuroelec/source/browse/trunk/Demo_Projects/Python-ColorPicker/Python-code/rgb.py?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/HP_RGB_LED_Shield_V1');
 changed_urls.push('/p/neuroelec/source/browse/trunk/HP_RGB_LED_Shield_V1?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/HP_RGB_LED_Shield_V2');
 changed_urls.push('/p/neuroelec/source/browse/trunk/HP_RGB_LED_Shield_V2?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/SoftI2cMaster');
 changed_urls.push('/p/neuroelec/source/browse/trunk/SoftI2cMaster?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/ad5254');
 changed_urls.push('/p/neuroelec/source/browse/trunk/ad5254?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/ffft');
 changed_urls.push('/p/neuroelec/source/browse/trunk/ffft?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/hardware');
 changed_urls.push('/p/neuroelec/source/browse/trunk/hardware?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/hardware/HP_RGB_LED_Shield_V1');
 changed_urls.push('/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V1?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/hardware/HP_RGB_LED_Shield_V1/HPLEDShield-v24.brd');
 changed_urls.push('/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V1/HPLEDShield-v24.brd?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/hardware/HP_RGB_LED_Shield_V1/HPLEDShield-v24.pdf');
 changed_urls.push('/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V1/HPLEDShield-v24.pdf?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/hardware/HP_RGB_LED_Shield_V1/HPLEDShield-v24.sch');
 changed_urls.push('/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V1/HPLEDShield-v24.sch?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/hardware/HP_RGB_LED_Shield_V1/HPLEDShield-v24Board.png');
 changed_urls.push('/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V1/HPLEDShield-v24Board.png?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/hardware/HP_RGB_LED_Shield_V1/HPLEDShield-v24Board_small.png');
 changed_urls.push('/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V1/HPLEDShield-v24Board_small.png?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/hardware/HP_RGB_LED_Shield_V1/HPLEDShield-v24Schematic.png');
 changed_urls.push('/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V1/HPLEDShield-v24Schematic.png?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/hardware/HP_RGB_LED_Shield_V1/HPLEDShield-v24Schematic_small.png');
 changed_urls.push('/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V1/HPLEDShield-v24Schematic_small.png?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/hardware/HP_RGB_LED_Shield_V2');
 changed_urls.push('/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V2?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/hardware/HP_RGB_LED_Shield_V2/HPLEDShield-v32.brd');
 changed_urls.push('/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V2/HPLEDShield-v32.brd?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/hardware/HP_RGB_LED_Shield_V2/HPLEDShield-v32.sch');
 changed_urls.push('/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V2/HPLEDShield-v32.sch?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/hardware/HP_RGB_LED_Shield_V2/HPLEDShield_brd-v32.pdf');
 changed_urls.push('/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V2/HPLEDShield_brd-v32.pdf?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/hardware/HP_RGB_LED_Shield_V2/HPLEDShield_brd-v32.png');
 changed_urls.push('/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V2/HPLEDShield_brd-v32.png?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/hardware/HP_RGB_LED_Shield_V2/HPLEDShield_sch-v32.pdf');
 changed_urls.push('/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V2/HPLEDShield_sch-v32.pdf?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/hardware/HP_RGB_LED_Shield_V2/HPLEDShield_sch-v32.png');
 changed_urls.push('/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V2/HPLEDShield_sch-v32.png?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/libraries');
 changed_urls.push('/p/neuroelec/source/browse/trunk/libraries?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/libraries/Arduino 1.0');
 changed_urls.push('/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1');
 changed_urls.push('/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB');
 changed_urls.push('/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/HPRGB.cpp');
 changed_urls.push('/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/HPRGB.cpp?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/HPRGB.h');
 changed_urls.push('/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/HPRGB.h?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/examples');
 changed_urls.push('/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/examples?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/examples/HPLEDShield');
 changed_urls.push('/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/examples/HPLEDShield?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/examples/HPLEDShield/HPLEDShield.ino');
 changed_urls.push('/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/examples/HPLEDShield/HPLEDShield.ino?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/examples/Temperature');
 changed_urls.push('/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/examples/Temperature?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/examples/Temperature/Temperature.ino');
 changed_urls.push('/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/examples/Temperature/Temperature.ino?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/examples/changeDeviceID');
 changed_urls.push('/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/examples/changeDeviceID?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/examples/changeDeviceID/changeDeviceID.ino');
 changed_urls.push('/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/examples/changeDeviceID/changeDeviceID.ino?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/keywords.txt');
 changed_urls.push('/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/keywords.txt?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V2');
 changed_urls.push('/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V2?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V2/HPRGB2');
 changed_urls.push('/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V2/HPRGB2?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V2/HPRGB2/HPRGB2.cpp');
 changed_urls.push('/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V2/HPRGB2/HPRGB2.cpp?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V2/HPRGB2/HPRGB2.h');
 changed_urls.push('/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V2/HPRGB2/HPRGB2.h?r\x3d21\x26spec\x3dsvn23');
 
 
 changed_paths.push('/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V2/HPRGB2/examples');
 changed_urls.push('/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V2/HPRGB2/examples?r\x3d21\x26spec\x3dsvn23');
 
 
 function getCurrentPageIndex() {
 for (var i = 0; i < changed_paths.length; i++) {
 if (selected_path == changed_paths[i]) {
 return i;
 }
 }
 }
 function getNextPage() {
 var i = getCurrentPageIndex();
 if (i < changed_paths.length - 1) {
 return changed_urls[i + 1];
 }
 return null;
 }
 function getPreviousPage() {
 var i = getCurrentPageIndex();
 if (i > 0) {
 return changed_urls[i - 1];
 }
 return null;
 }
 function gotoNextPage() {
 var page = getNextPage();
 if (!page) {
 page = detail_url;
 }
 window.location = page;
 }
 function gotoPreviousPage() {
 var page = getPreviousPage();
 if (!page) {
 page = detail_url;
 }
 window.location = page;
 }
 function gotoDetailPage() {
 window.location = detail_url;
 }
 function gotoPublishPage() {
 window.location = publish_url;
 }
</script>

 
 <style type="text/css">
 #review_nav {
 border-top: 3px solid white;
 padding-top: 6px;
 margin-top: 1em;
 }
 #review_nav td {
 vertical-align: middle;
 }
 #review_nav select {
 margin: .5em 0;
 }
 </style>
 <div id="review_nav">
 <table><tr><td>Go to:&nbsp;</td><td>
 <select name="files_in_rev" onchange="window.location=this.value">
 
 <option value="/p/neuroelec/source/browse/trunk/Demo_Projects?r=21&amp;spec=svn23"
 
 >/trunk/Demo_Projects</option>
 
 <option value="/p/neuroelec/source/browse/trunk/Demo_Projects/LEDColorPicker?r=21&amp;spec=svn23"
 
 >/trunk/Demo_Projects/LEDColorPicker</option>
 
 <option value="/p/neuroelec/source/browse/trunk/Demo_Projects/LEDColorPicker/LEDColorPicker.pde?r=21&amp;spec=svn23"
 
 >...EDColorPicker/LEDColorPicker.pde</option>
 
 <option value="/p/neuroelec/source/browse/trunk/Demo_Projects/Python-ColorPicker?r=21&amp;spec=svn23"
 
 >...Demo_Projects/Python-ColorPicker</option>
 
 <option value="/p/neuroelec/source/browse/trunk/Demo_Projects/Python-ColorPicker/Python-ColorPicker.pde?r=21&amp;spec=svn23"
 
 >...lorPicker/Python-ColorPicker.pde</option>
 
 <option value="/p/neuroelec/source/browse/trunk/Demo_Projects/Python-ColorPicker/Python-code?r=21&amp;spec=svn23"
 
 >...s/Python-ColorPicker/Python-code</option>
 
 <option value="/p/neuroelec/source/browse/trunk/Demo_Projects/Python-ColorPicker/Python-code/arduino-rgb.py?r=21&amp;spec=svn23"
 
 >...icker/Python-code/arduino-rgb.py</option>
 
 <option value="/p/neuroelec/source/browse/trunk/Demo_Projects/Python-ColorPicker/Python-code/gtk-color-picker.py?r=21&amp;spec=svn23"
 
 >.../Python-code/gtk-color-picker.py</option>
 
 <option value="/p/neuroelec/source/browse/trunk/Demo_Projects/Python-ColorPicker/Python-code/hsv.py?r=21&amp;spec=svn23"
 
 >...n-ColorPicker/Python-code/hsv.py</option>
 
 <option value="/p/neuroelec/source/browse/trunk/Demo_Projects/Python-ColorPicker/Python-code/rgb.py?r=21&amp;spec=svn23"
 
 >...n-ColorPicker/Python-code/rgb.py</option>
 
 <option value="/p/neuroelec/source/browse/trunk/HP_RGB_LED_Shield_V1?r=21&amp;spec=svn23"
 
 >/trunk/HP_RGB_LED_Shield_V1</option>
 
 <option value="/p/neuroelec/source/browse/trunk/HP_RGB_LED_Shield_V2?r=21&amp;spec=svn23"
 
 >/trunk/HP_RGB_LED_Shield_V2</option>
 
 <option value="/p/neuroelec/source/browse/trunk/SoftI2cMaster?r=21&amp;spec=svn23"
 
 >/trunk/SoftI2cMaster</option>
 
 <option value="/p/neuroelec/source/browse/trunk/ad5254?r=21&amp;spec=svn23"
 
 >/trunk/ad5254</option>
 
 <option value="/p/neuroelec/source/browse/trunk/ffft?r=21&amp;spec=svn23"
 
 >/trunk/ffft</option>
 
 <option value="/p/neuroelec/source/browse/trunk/hardware?r=21&amp;spec=svn23"
 
 >/trunk/hardware</option>
 
 <option value="/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V1?r=21&amp;spec=svn23"
 
 >...nk/hardware/HP_RGB_LED_Shield_V1</option>
 
 <option value="/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V1/HPLEDShield-v24.brd?r=21&amp;spec=svn23"
 
 >...ED_Shield_V1/HPLEDShield-v24.brd</option>
 
 <option value="/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V1/HPLEDShield-v24.pdf?r=21&amp;spec=svn23"
 
 >...ED_Shield_V1/HPLEDShield-v24.pdf</option>
 
 <option value="/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V1/HPLEDShield-v24.sch?r=21&amp;spec=svn23"
 
 >...ED_Shield_V1/HPLEDShield-v24.sch</option>
 
 <option value="/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V1/HPLEDShield-v24Board.png?r=21&amp;spec=svn23"
 
 >...ield_V1/HPLEDShield-v24Board.png</option>
 
 <option value="/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V1/HPLEDShield-v24Board_small.png?r=21&amp;spec=svn23"
 
 >...1/HPLEDShield-v24Board_small.png</option>
 
 <option value="/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V1/HPLEDShield-v24Schematic.png?r=21&amp;spec=svn23"
 
 >..._V1/HPLEDShield-v24Schematic.png</option>
 
 <option value="/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V1/HPLEDShield-v24Schematic_small.png?r=21&amp;spec=svn23"
 
 >...LEDShield-v24Schematic_small.png</option>
 
 <option value="/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V2?r=21&amp;spec=svn23"
 
 >...nk/hardware/HP_RGB_LED_Shield_V2</option>
 
 <option value="/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V2/HPLEDShield-v32.brd?r=21&amp;spec=svn23"
 
 >...ED_Shield_V2/HPLEDShield-v32.brd</option>
 
 <option value="/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V2/HPLEDShield-v32.sch?r=21&amp;spec=svn23"
 
 >...ED_Shield_V2/HPLEDShield-v32.sch</option>
 
 <option value="/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V2/HPLEDShield_brd-v32.pdf?r=21&amp;spec=svn23"
 
 >...hield_V2/HPLEDShield_brd-v32.pdf</option>
 
 <option value="/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V2/HPLEDShield_brd-v32.png?r=21&amp;spec=svn23"
 
 >...hield_V2/HPLEDShield_brd-v32.png</option>
 
 <option value="/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V2/HPLEDShield_sch-v32.pdf?r=21&amp;spec=svn23"
 
 >...hield_V2/HPLEDShield_sch-v32.pdf</option>
 
 <option value="/p/neuroelec/source/browse/trunk/hardware/HP_RGB_LED_Shield_V2/HPLEDShield_sch-v32.png?r=21&amp;spec=svn23"
 
 >...hield_V2/HPLEDShield_sch-v32.png</option>
 
 <option value="/p/neuroelec/source/browse/trunk/libraries?r=21&amp;spec=svn23"
 
 >/trunk/libraries</option>
 
 <option value="/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0?r=21&amp;spec=svn23"
 
 >/trunk/libraries/Arduino 1.0</option>
 
 <option value="/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1?r=21&amp;spec=svn23"
 
 >...Arduino 1.0/HP_RGB_LED_Shield_V1</option>
 
 <option value="/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB?r=21&amp;spec=svn23"
 
 >...o 1.0/HP_RGB_LED_Shield_V1/HPRGB</option>
 
 <option value="/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/HPRGB.cpp?r=21&amp;spec=svn23"
 
 >...GB_LED_Shield_V1/HPRGB/HPRGB.cpp</option>
 
 <option value="/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/HPRGB.h?r=21&amp;spec=svn23"
 
 >..._RGB_LED_Shield_V1/HPRGB/HPRGB.h</option>
 
 <option value="/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/examples?r=21&amp;spec=svn23"
 
 >...RGB_LED_Shield_V1/HPRGB/examples</option>
 
 <option value="/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/examples/HPLEDShield?r=21&amp;spec=svn23"
 
 >...ld_V1/HPRGB/examples/HPLEDShield</option>
 
 <option value="/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/examples/HPLEDShield/HPLEDShield.ino?r=21&amp;spec=svn23"
 
 >...ples/HPLEDShield/HPLEDShield.ino</option>
 
 <option value="/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/examples/Temperature?r=21&amp;spec=svn23"
 
 >...ld_V1/HPRGB/examples/Temperature</option>
 
 <option value="/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/examples/Temperature/Temperature.ino?r=21&amp;spec=svn23"
 
 >...ples/Temperature/Temperature.ino</option>
 
 <option value="/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/examples/changeDeviceID?r=21&amp;spec=svn23"
 
 >...V1/HPRGB/examples/changeDeviceID</option>
 
 <option value="/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/examples/changeDeviceID/changeDeviceID.ino?r=21&amp;spec=svn23"
 
 >...hangeDeviceID/changeDeviceID.ino</option>
 
 <option value="/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V1/HPRGB/keywords.txt?r=21&amp;spec=svn23"
 
 >...LED_Shield_V1/HPRGB/keywords.txt</option>
 
 <option value="/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V2?r=21&amp;spec=svn23"
 
 >...Arduino 1.0/HP_RGB_LED_Shield_V2</option>
 
 <option value="/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V2/HPRGB2?r=21&amp;spec=svn23"
 
 >... 1.0/HP_RGB_LED_Shield_V2/HPRGB2</option>
 
 <option value="/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V2/HPRGB2/HPRGB2.cpp?r=21&amp;spec=svn23"
 
 >..._LED_Shield_V2/HPRGB2/HPRGB2.cpp</option>
 
 <option value="/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V2/HPRGB2/HPRGB2.h?r=21&amp;spec=svn23"
 
 >...GB_LED_Shield_V2/HPRGB2/HPRGB2.h</option>
 
 <option value="/p/neuroelec/source/browse/trunk/libraries/Arduino 1.0/HP_RGB_LED_Shield_V2/HPRGB2/examples?r=21&amp;spec=svn23"
 
 >...GB_LED_Shield_V2/HPRGB2/examples</option>
 
 </select>
 </td></tr></table>
 
 
 



 <div style="white-space:nowrap">
 Project members,
 <a href="https://www.google.com/accounts/ServiceLogin?service=code&amp;ltmpl=phosting&amp;continue=http%3A%2F%2Fcode.google.com%2Fp%2Fneuroelec%2Fsource%2Fbrowse%2Ftrunk%2Flibraries%2FArduino%25201.0%2Fffft%2Fffft.S&amp;followup=http%3A%2F%2Fcode.google.com%2Fp%2Fneuroelec%2Fsource%2Fbrowse%2Ftrunk%2Flibraries%2FArduino%25201.0%2Fffft%2Fffft.S"
 >sign in</a> to write a code review</div>


 
 </div>
 
 
 </div>
 <div class="round1"></div>
 <div class="round2"></div>
 <div class="round4"></div>
 </div>
 <div class="pmeta_bubble_bg" style="border:1px solid white">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <div id="older_bubble">
 <p>Older revisions</p>
 
 <a href="/p/neuroelec/source/list?path=/trunk/libraries/Arduino+1.0/ffft/ffft.S&start=21">All revisions of this file</a>
 </div>
 </div>
 <div class="round1"></div>
 <div class="round2"></div>
 <div class="round4"></div>
 </div>
 
 <div class="pmeta_bubble_bg" style="border:1px solid white">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <div id="fileinfo_bubble">
 <p>File info</p>
 
 <div>Size: 50375 bytes,
 677 lines</div>
 
 <div><a href="//neuroelec.googlecode.com/svn/trunk/libraries/Arduino 1.0/ffft/ffft.S">View raw file</a></div>
 </div>
 
 </div>
 <div class="round1"></div>
 <div class="round2"></div>
 <div class="round4"></div>
 </div>
 </div>
 </div>


</div>

</div>
</div>


<script src="http://www.gstatic.com/codesite/ph/16216231599268812631/js/source_file_scripts.js"></script>

 <script type="text/javascript" src="https://kibbles.googlecode.com/files/kibbles-1.3.3.comp.js"></script>
 <script type="text/javascript">
 var lastStop = null;
 var initialized = false;
 
 function updateCursor(next, prev) {
 if (prev && prev.element) {
 prev.element.className = 'cursor_stop cursor_hidden';
 }
 if (next && next.element) {
 next.element.className = 'cursor_stop cursor';
 lastStop = next.index;
 }
 }
 
 function pubRevealed(data) {
 updateCursorForCell(data.cellId, 'cursor_stop cursor_hidden');
 if (initialized) {
 reloadCursors();
 }
 }
 
 function draftRevealed(data) {
 updateCursorForCell(data.cellId, 'cursor_stop cursor_hidden');
 if (initialized) {
 reloadCursors();
 }
 }
 
 function draftDestroyed(data) {
 updateCursorForCell(data.cellId, 'nocursor');
 if (initialized) {
 reloadCursors();
 }
 }
 function reloadCursors() {
 kibbles.skipper.reset();
 loadCursors();
 if (lastStop != null) {
 kibbles.skipper.setCurrentStop(lastStop);
 }
 }
 // possibly the simplest way to insert any newly added comments
 // is to update the class of the corresponding cursor row,
 // then refresh the entire list of rows.
 function updateCursorForCell(cellId, className) {
 var cell = document.getElementById(cellId);
 // we have to go two rows back to find the cursor location
 var row = getPreviousElement(cell.parentNode);
 row.className = className;
 }
 // returns the previous element, ignores text nodes.
 function getPreviousElement(e) {
 var element = e.previousSibling;
 if (element.nodeType == 3) {
 element = element.previousSibling;
 }
 if (element && element.tagName) {
 return element;
 }
 }
 function loadCursors() {
 // register our elements with skipper
 var elements = CR_getElements('*', 'cursor_stop');
 var len = elements.length;
 for (var i = 0; i < len; i++) {
 var element = elements[i]; 
 element.className = 'cursor_stop cursor_hidden';
 kibbles.skipper.append(element);
 }
 }
 function toggleComments() {
 CR_toggleCommentDisplay();
 reloadCursors();
 }
 function keysOnLoadHandler() {
 // setup skipper
 kibbles.skipper.addStopListener(
 kibbles.skipper.LISTENER_TYPE.PRE, updateCursor);
 // Set the 'offset' option to return the middle of the client area
 // an option can be a static value, or a callback
 kibbles.skipper.setOption('padding_top', 50);
 // Set the 'offset' option to return the middle of the client area
 // an option can be a static value, or a callback
 kibbles.skipper.setOption('padding_bottom', 100);
 // Register our keys
 kibbles.skipper.addFwdKey("n");
 kibbles.skipper.addRevKey("p");
 kibbles.keys.addKeyPressListener(
 'u', function() { window.location = detail_url; });
 kibbles.keys.addKeyPressListener(
 'r', function() { window.location = detail_url + '#publish'; });
 
 kibbles.keys.addKeyPressListener('j', gotoNextPage);
 kibbles.keys.addKeyPressListener('k', gotoPreviousPage);
 
 
 }
 </script>
<script src="http://www.gstatic.com/codesite/ph/16216231599268812631/js/code_review_scripts.js"></script>
<script type="text/javascript">
 function showPublishInstructions() {
 var element = document.getElementById('review_instr');
 if (element) {
 element.className = 'opened';
 }
 }
 var codereviews;
 function revsOnLoadHandler() {
 // register our source container with the commenting code
 var paths = {'svn23': '/trunk/libraries/Arduino 1.0/ffft/ffft.S'}
 codereviews = CR_controller.setup(
 {"profileUrl":null,"token":null,"assetHostPath":"http://www.gstatic.com/codesite/ph","domainName":null,"assetVersionPath":"http://www.gstatic.com/codesite/ph/16216231599268812631","projectHomeUrl":"/p/neuroelec","relativeBaseUrl":"","projectName":"neuroelec","loggedInUserEmail":null}, '', 'svn23', paths,
 CR_BrowseIntegrationFactory);
 
 codereviews.registerActivityListener(CR_ActivityType.REVEAL_DRAFT_PLATE, showPublishInstructions);
 
 codereviews.registerActivityListener(CR_ActivityType.REVEAL_PUB_PLATE, pubRevealed);
 codereviews.registerActivityListener(CR_ActivityType.REVEAL_DRAFT_PLATE, draftRevealed);
 codereviews.registerActivityListener(CR_ActivityType.DISCARD_DRAFT_COMMENT, draftDestroyed);
 
 
 
 
 
 
 
 var initialized = true;
 reloadCursors();
 }
 window.onload = function() {keysOnLoadHandler(); revsOnLoadHandler();};

</script>
<script type="text/javascript" src="http://www.gstatic.com/codesite/ph/16216231599268812631/js/dit_scripts.js"></script>

 
 
 
 <script type="text/javascript" src="http://www.gstatic.com/codesite/ph/16216231599268812631/js/ph_core.js"></script>
 
 
 
 
 <script type="text/javascript" src="/js/codesite_product_dictionary_ph.pack.04102009.js"></script>
</div> 
<div id="footer" dir="ltr">
 <div class="text">
 &copy;2011 Google -
 <a href="/projecthosting/terms.html">Terms</a> -
 <a href="http://www.google.com/privacy.html">Privacy</a> -
 <a href="/p/support/">Project Hosting Help</a>
 </div>
</div>
 <div class="hostedBy" style="margin-top: -20px;">
 <span style="vertical-align: top;">Powered by <a href="http://code.google.com/projecthosting/">Google Project Hosting</a></span>
 </div>
 
 


 
 </body>
</html>

