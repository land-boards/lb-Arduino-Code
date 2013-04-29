



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
 
 
 <title>ffft.h - 
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
 | <a href="https://www.google.com/accounts/ServiceLogin?service=code&amp;ltmpl=phosting&amp;continue=http%3A%2F%2Fcode.google.com%2Fp%2Fneuroelec%2Fsource%2Fbrowse%2Ftrunk%2Flibraries%2FArduino%25201.0%2Fffft%2Fffft.h&amp;followup=http%3A%2F%2Fcode.google.com%2Fp%2Fneuroelec%2Fsource%2Fbrowse%2Ftrunk%2Flibraries%2FArduino%25201.0%2Fffft%2Fffft.h" onclick="_CS_click('/gb/ph/signin');"><u>Sign in</u></a>
 
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
 <span id="crumb_links" class="ifClosed"><a href="/p/neuroelec/source/browse/trunk/">trunk</a><span class="sp">/&nbsp;</span><a href="/p/neuroelec/source/browse/trunk/libraries/">libraries</a><span class="sp">/&nbsp;</span><a href="/p/neuroelec/source/browse/trunk/libraries/Arduino+1.0/">Arduino 1.0</a><span class="sp">/&nbsp;</span><a href="/p/neuroelec/source/browse/trunk/libraries/Arduino+1.0/ffft/">ffft</a><span class="sp">/&nbsp;</span>ffft.h</span>
 
 

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
></table></pre>
<pre><table width="100%"><tr class="nocursor"><td></td></tr></table></pre>
</td>
<td id="lines">
<pre><table width="100%"><tr class="cursor_stop cursor_hidden"><td></td></tr></table></pre>
<pre class="prettyprint "><table id="src_table_0"><tr
id=sl_svn23_1

><td class="source">#ifndef FFT_N<br></td></tr
><tr
id=sl_svn23_2

><td class="source">#define FFT_N	128		/* Number of samples (64,128,256,512). Don&#39;t forget to clean! */<br></td></tr
><tr
id=sl_svn23_3

><td class="source">//#define INPUT_NOUSE<br></td></tr
><tr
id=sl_svn23_4

><td class="source">//#define INPUT_IQ<br></td></tr
><tr
id=sl_svn23_5

><td class="source"><br></td></tr
><tr
id=sl_svn23_6

><td class="source">#ifndef FFFT_ASM	/* for c modules */<br></td></tr
><tr
id=sl_svn23_7

><td class="source"><br></td></tr
><tr
id=sl_svn23_8

><td class="source">typedef struct _tag_complex_t {<br></td></tr
><tr
id=sl_svn23_9

><td class="source">	int16_t	r;<br></td></tr
><tr
id=sl_svn23_10

><td class="source">	int16_t i;<br></td></tr
><tr
id=sl_svn23_11

><td class="source">} complex_t;<br></td></tr
><tr
id=sl_svn23_12

><td class="source"><br></td></tr
><tr
id=sl_svn23_13

><td class="source"><br></td></tr
><tr
id=sl_svn23_14

><td class="source">#ifndef INPUT_NOUSE<br></td></tr
><tr
id=sl_svn23_15

><td class="source">#ifdef INPUT_IQ<br></td></tr
><tr
id=sl_svn23_16

><td class="source">void fft_input (const complex_t *, complex_t *);<br></td></tr
><tr
id=sl_svn23_17

><td class="source">#else<br></td></tr
><tr
id=sl_svn23_18

><td class="source">extern &quot;C&quot; { void fft_input (const int16_t *, complex_t *); }<br></td></tr
><tr
id=sl_svn23_19

><td class="source">#endif<br></td></tr
><tr
id=sl_svn23_20

><td class="source">#endif<br></td></tr
><tr
id=sl_svn23_21

><td class="source">extern &quot;C&quot; {<br></td></tr
><tr
id=sl_svn23_22

><td class="source">void fft_execute (complex_t *);<br></td></tr
><tr
id=sl_svn23_23

><td class="source">void fft_output (complex_t *, uint16_t *);<br></td></tr
><tr
id=sl_svn23_24

><td class="source">int16_t fmuls_f (int16_t, int16_t);<br></td></tr
><tr
id=sl_svn23_25

><td class="source">} <br></td></tr
><tr
id=sl_svn23_26

><td class="source">#include &lt;avr/pgmspace.h&gt;<br></td></tr
><tr
id=sl_svn23_27

><td class="source">extern const prog_int16_t tbl_window[];<br></td></tr
><tr
id=sl_svn23_28

><td class="source"><br></td></tr
><tr
id=sl_svn23_29

><td class="source"><br></td></tr
><tr
id=sl_svn23_30

><td class="source"><br></td></tr
><tr
id=sl_svn23_31

><td class="source">#else				/* for asm module */<br></td></tr
><tr
id=sl_svn23_32

><td class="source"><br></td></tr
><tr
id=sl_svn23_33

><td class="source">#define T0L	r0<br></td></tr
><tr
id=sl_svn23_34

><td class="source">#define T0H	r1<br></td></tr
><tr
id=sl_svn23_35

><td class="source">#define T2L	r2<br></td></tr
><tr
id=sl_svn23_36

><td class="source">#define T2H	r3<br></td></tr
><tr
id=sl_svn23_37

><td class="source">#define T4L	r4<br></td></tr
><tr
id=sl_svn23_38

><td class="source">#define T4H	r5<br></td></tr
><tr
id=sl_svn23_39

><td class="source">#define T6L	r6<br></td></tr
><tr
id=sl_svn23_40

><td class="source">#define T6H	r7<br></td></tr
><tr
id=sl_svn23_41

><td class="source">#define T8L	r8<br></td></tr
><tr
id=sl_svn23_42

><td class="source">#define T8H	r9<br></td></tr
><tr
id=sl_svn23_43

><td class="source">#define T10L	r10<br></td></tr
><tr
id=sl_svn23_44

><td class="source">#define T10H	r11<br></td></tr
><tr
id=sl_svn23_45

><td class="source">#define T12L	r12<br></td></tr
><tr
id=sl_svn23_46

><td class="source">#define T12H	r13<br></td></tr
><tr
id=sl_svn23_47

><td class="source">#define T14L	r14<br></td></tr
><tr
id=sl_svn23_48

><td class="source">#define T14H	r15<br></td></tr
><tr
id=sl_svn23_49

><td class="source">#define AL	r16<br></td></tr
><tr
id=sl_svn23_50

><td class="source">#define AH	r17<br></td></tr
><tr
id=sl_svn23_51

><td class="source">#define BL	r18<br></td></tr
><tr
id=sl_svn23_52

><td class="source">#define BH	r19<br></td></tr
><tr
id=sl_svn23_53

><td class="source">#define CL	r20<br></td></tr
><tr
id=sl_svn23_54

><td class="source">#define CH	r21<br></td></tr
><tr
id=sl_svn23_55

><td class="source">#define DL	r22<br></td></tr
><tr
id=sl_svn23_56

><td class="source">#define DH	r23<br></td></tr
><tr
id=sl_svn23_57

><td class="source">#define EL	r24<br></td></tr
><tr
id=sl_svn23_58

><td class="source">#define EH	r25<br></td></tr
><tr
id=sl_svn23_59

><td class="source">#define XL	r26<br></td></tr
><tr
id=sl_svn23_60

><td class="source">#define XH	r27<br></td></tr
><tr
id=sl_svn23_61

><td class="source">#define YL	r28<br></td></tr
><tr
id=sl_svn23_62

><td class="source">#define YH	r29<br></td></tr
><tr
id=sl_svn23_63

><td class="source">#define ZL	r30<br></td></tr
><tr
id=sl_svn23_64

><td class="source">#define ZH	r31<br></td></tr
><tr
id=sl_svn23_65

><td class="source"><br></td></tr
><tr
id=sl_svn23_66

><td class="source">.macro	ldiw	dh,dl, abs<br></td></tr
><tr
id=sl_svn23_67

><td class="source">	ldi	\dl, lo8(\abs)<br></td></tr
><tr
id=sl_svn23_68

><td class="source">	ldi	\dh, hi8(\abs)<br></td></tr
><tr
id=sl_svn23_69

><td class="source">.endm<br></td></tr
><tr
id=sl_svn23_70

><td class="source"><br></td></tr
><tr
id=sl_svn23_71

><td class="source">.macro	subiw	dh,dl, abs<br></td></tr
><tr
id=sl_svn23_72

><td class="source">	subi	\dl, lo8(\abs)<br></td></tr
><tr
id=sl_svn23_73

><td class="source">	sbci	\dh, hi8(\abs)<br></td></tr
><tr
id=sl_svn23_74

><td class="source">.endm<br></td></tr
><tr
id=sl_svn23_75

><td class="source"><br></td></tr
><tr
id=sl_svn23_76

><td class="source">.macro	addw	dh,dl, sh,sl<br></td></tr
><tr
id=sl_svn23_77

><td class="source">	add	\dl, \sl<br></td></tr
><tr
id=sl_svn23_78

><td class="source">	adc	\dh, \sh<br></td></tr
><tr
id=sl_svn23_79

><td class="source">.endm<br></td></tr
><tr
id=sl_svn23_80

><td class="source"><br></td></tr
><tr
id=sl_svn23_81

><td class="source">.macro	addd	d3,d2,d1,d0, s3,s2,s1,s0<br></td></tr
><tr
id=sl_svn23_82

><td class="source">	add	\d0, \s0<br></td></tr
><tr
id=sl_svn23_83

><td class="source">	adc	\d1, \s1<br></td></tr
><tr
id=sl_svn23_84

><td class="source">	adc	\d2, \s2<br></td></tr
><tr
id=sl_svn23_85

><td class="source">	adc	\d3, \s3<br></td></tr
><tr
id=sl_svn23_86

><td class="source">.endm<br></td></tr
><tr
id=sl_svn23_87

><td class="source"><br></td></tr
><tr
id=sl_svn23_88

><td class="source">.macro	subw	dh,dl, sh,sl<br></td></tr
><tr
id=sl_svn23_89

><td class="source">	sub	\dl, \sl<br></td></tr
><tr
id=sl_svn23_90

><td class="source">	sbc	\dh, \sh<br></td></tr
><tr
id=sl_svn23_91

><td class="source">.endm<br></td></tr
><tr
id=sl_svn23_92

><td class="source"><br></td></tr
><tr
id=sl_svn23_93

><td class="source">.macro	subd	d3,d2,d1,d0, s3,s2,s1,s0<br></td></tr
><tr
id=sl_svn23_94

><td class="source">	sub	\d0, \s0<br></td></tr
><tr
id=sl_svn23_95

><td class="source">	sbc	\d1, \s1<br></td></tr
><tr
id=sl_svn23_96

><td class="source">	sbc	\d2, \s2<br></td></tr
><tr
id=sl_svn23_97

><td class="source">	sbc	\d3, \s3<br></td></tr
><tr
id=sl_svn23_98

><td class="source">.endm<br></td></tr
><tr
id=sl_svn23_99

><td class="source"><br></td></tr
><tr
id=sl_svn23_100

><td class="source">.macro	lddw	dh,dl, src<br></td></tr
><tr
id=sl_svn23_101

><td class="source">	ldd	\dl, \src<br></td></tr
><tr
id=sl_svn23_102

><td class="source">	ldd	\dh, \src+1<br></td></tr
><tr
id=sl_svn23_103

><td class="source">.endm<br></td></tr
><tr
id=sl_svn23_104

><td class="source"><br></td></tr
><tr
id=sl_svn23_105

><td class="source">.macro	ldw	dh,dl, src<br></td></tr
><tr
id=sl_svn23_106

><td class="source">	ld	\dl, \src<br></td></tr
><tr
id=sl_svn23_107

><td class="source">	ld	\dh, \src<br></td></tr
><tr
id=sl_svn23_108

><td class="source">.endm<br></td></tr
><tr
id=sl_svn23_109

><td class="source"><br></td></tr
><tr
id=sl_svn23_110

><td class="source">.macro	stw	dst, sh,sl<br></td></tr
><tr
id=sl_svn23_111

><td class="source">	st	\dst, \sl<br></td></tr
><tr
id=sl_svn23_112

><td class="source">	st	\dst, \sh<br></td></tr
><tr
id=sl_svn23_113

><td class="source">.endm<br></td></tr
><tr
id=sl_svn23_114

><td class="source"><br></td></tr
><tr
id=sl_svn23_115

><td class="source">.macro	clrw	dh, dl<br></td></tr
><tr
id=sl_svn23_116

><td class="source">	clr	\dh<br></td></tr
><tr
id=sl_svn23_117

><td class="source">	clr	\dl<br></td></tr
><tr
id=sl_svn23_118

><td class="source">.endm<br></td></tr
><tr
id=sl_svn23_119

><td class="source"><br></td></tr
><tr
id=sl_svn23_120

><td class="source">.macro	lsrw	dh, dl<br></td></tr
><tr
id=sl_svn23_121

><td class="source">	lsr	\dh<br></td></tr
><tr
id=sl_svn23_122

><td class="source">	ror	\dl<br></td></tr
><tr
id=sl_svn23_123

><td class="source">.endm<br></td></tr
><tr
id=sl_svn23_124

><td class="source"><br></td></tr
><tr
id=sl_svn23_125

><td class="source">.macro	asrw	dh, dl<br></td></tr
><tr
id=sl_svn23_126

><td class="source">	asr	\dh<br></td></tr
><tr
id=sl_svn23_127

><td class="source">	ror	\dl<br></td></tr
><tr
id=sl_svn23_128

><td class="source">.endm<br></td></tr
><tr
id=sl_svn23_129

><td class="source"><br></td></tr
><tr
id=sl_svn23_130

><td class="source">.macro	lslw	dh, dl<br></td></tr
><tr
id=sl_svn23_131

><td class="source">	lsl	\dl<br></td></tr
><tr
id=sl_svn23_132

><td class="source">	rol	\dh<br></td></tr
><tr
id=sl_svn23_133

><td class="source">.endm<br></td></tr
><tr
id=sl_svn23_134

><td class="source"><br></td></tr
><tr
id=sl_svn23_135

><td class="source">.macro	pushw	dh, dl<br></td></tr
><tr
id=sl_svn23_136

><td class="source">	push	\dh<br></td></tr
><tr
id=sl_svn23_137

><td class="source">	push	\dl<br></td></tr
><tr
id=sl_svn23_138

><td class="source">.endm<br></td></tr
><tr
id=sl_svn23_139

><td class="source"><br></td></tr
><tr
id=sl_svn23_140

><td class="source">.macro	popw	dh, dl<br></td></tr
><tr
id=sl_svn23_141

><td class="source">	pop	\dl<br></td></tr
><tr
id=sl_svn23_142

><td class="source">	pop	\dh<br></td></tr
><tr
id=sl_svn23_143

><td class="source">.endm<br></td></tr
><tr
id=sl_svn23_144

><td class="source"><br></td></tr
><tr
id=sl_svn23_145

><td class="source">.macro	lpmw	dh,dl, src<br></td></tr
><tr
id=sl_svn23_146

><td class="source">	lpm	\dl, \src<br></td></tr
><tr
id=sl_svn23_147

><td class="source">	lpm	\dh, \src<br></td></tr
><tr
id=sl_svn23_148

><td class="source">.endm<br></td></tr
><tr
id=sl_svn23_149

><td class="source"><br></td></tr
><tr
id=sl_svn23_150

><td class="source">.macro	rjne	lbl<br></td></tr
><tr
id=sl_svn23_151

><td class="source">	breq	99f<br></td></tr
><tr
id=sl_svn23_152

><td class="source">	rjmp	\lbl<br></td></tr
><tr
id=sl_svn23_153

><td class="source">99:<br></td></tr
><tr
id=sl_svn23_154

><td class="source">.endm<br></td></tr
><tr
id=sl_svn23_155

><td class="source"><br></td></tr
><tr
id=sl_svn23_156

><td class="source"><br></td></tr
><tr
id=sl_svn23_157

><td class="source">.macro	FMULS16	d3,d2,d1,d0 ,s1h,s1l, s2h,s2l	;Fractional Multiply (19clk)<br></td></tr
><tr
id=sl_svn23_158

><td class="source">	fmuls	\s1h, \s2h<br></td></tr
><tr
id=sl_svn23_159

><td class="source">	movw	\d2, T0L<br></td></tr
><tr
id=sl_svn23_160

><td class="source">	fmul	\s1l, \s2l<br></td></tr
><tr
id=sl_svn23_161

><td class="source">	movw	\d0, T0L<br></td></tr
><tr
id=sl_svn23_162

><td class="source">	adc	\d2, EH ;EH: zero reg.<br></td></tr
><tr
id=sl_svn23_163

><td class="source">	fmulsu	\s1h, \s2l<br></td></tr
><tr
id=sl_svn23_164

><td class="source">	sbc	\d3, EH<br></td></tr
><tr
id=sl_svn23_165

><td class="source">	add	\d1, T0L<br></td></tr
><tr
id=sl_svn23_166

><td class="source">	adc	\d2, T0H<br></td></tr
><tr
id=sl_svn23_167

><td class="source">	adc	\d3, EH<br></td></tr
><tr
id=sl_svn23_168

><td class="source">	fmulsu	\s2h, \s1l<br></td></tr
><tr
id=sl_svn23_169

><td class="source">	sbc	\d3, EH<br></td></tr
><tr
id=sl_svn23_170

><td class="source">	add	\d1, T0L<br></td></tr
><tr
id=sl_svn23_171

><td class="source">	adc	\d2, T0H<br></td></tr
><tr
id=sl_svn23_172

><td class="source">	adc	\d3, EH<br></td></tr
><tr
id=sl_svn23_173

><td class="source">.endm<br></td></tr
><tr
id=sl_svn23_174

><td class="source"><br></td></tr
><tr
id=sl_svn23_175

><td class="source"><br></td></tr
><tr
id=sl_svn23_176

><td class="source">.macro	SQRT32	; 32bit square root (526..542clk)<br></td></tr
><tr
id=sl_svn23_177

><td class="source">	clr	T6L<br></td></tr
><tr
id=sl_svn23_178

><td class="source">	clr	T6H<br></td></tr
><tr
id=sl_svn23_179

><td class="source">	clr	T8L<br></td></tr
><tr
id=sl_svn23_180

><td class="source">	clr	T8H<br></td></tr
><tr
id=sl_svn23_181

><td class="source">	ldi	BL, 1<br></td></tr
><tr
id=sl_svn23_182

><td class="source">	ldi	BH, 0<br></td></tr
><tr
id=sl_svn23_183

><td class="source">	clr	CL<br></td></tr
><tr
id=sl_svn23_184

><td class="source">	clr	CH<br></td></tr
><tr
id=sl_svn23_185

><td class="source">	ldi	DH, 16<br></td></tr
><tr
id=sl_svn23_186

><td class="source">90:	lsl	T2L<br></td></tr
><tr
id=sl_svn23_187

><td class="source">	rol	T2H<br></td></tr
><tr
id=sl_svn23_188

><td class="source">	rol	T4L<br></td></tr
><tr
id=sl_svn23_189

><td class="source">	rol	T4H<br></td></tr
><tr
id=sl_svn23_190

><td class="source">	rol	T6L<br></td></tr
><tr
id=sl_svn23_191

><td class="source">	rol	T6H<br></td></tr
><tr
id=sl_svn23_192

><td class="source">	rol	T8L<br></td></tr
><tr
id=sl_svn23_193

><td class="source">	rol	T8H<br></td></tr
><tr
id=sl_svn23_194

><td class="source">	lsl	T2L<br></td></tr
><tr
id=sl_svn23_195

><td class="source">	rol	T2H<br></td></tr
><tr
id=sl_svn23_196

><td class="source">	rol	T4L<br></td></tr
><tr
id=sl_svn23_197

><td class="source">	rol	T4H<br></td></tr
><tr
id=sl_svn23_198

><td class="source">	rol	T6L<br></td></tr
><tr
id=sl_svn23_199

><td class="source">	rol	T6H<br></td></tr
><tr
id=sl_svn23_200

><td class="source">	rol	T8L<br></td></tr
><tr
id=sl_svn23_201

><td class="source">	rol	T8H<br></td></tr
><tr
id=sl_svn23_202

><td class="source">	brpl	91f<br></td></tr
><tr
id=sl_svn23_203

><td class="source">	add	T6L, BL<br></td></tr
><tr
id=sl_svn23_204

><td class="source">	adc	T6H, BH<br></td></tr
><tr
id=sl_svn23_205

><td class="source">	adc	T8L, CL<br></td></tr
><tr
id=sl_svn23_206

><td class="source">	adc	T8H, CH<br></td></tr
><tr
id=sl_svn23_207

><td class="source">	rjmp	92f<br></td></tr
><tr
id=sl_svn23_208

><td class="source">91:	sub	T6L, BL<br></td></tr
><tr
id=sl_svn23_209

><td class="source">	sbc	T6H, BH<br></td></tr
><tr
id=sl_svn23_210

><td class="source">	sbc	T8L, CL<br></td></tr
><tr
id=sl_svn23_211

><td class="source">	sbc	T8H, CH<br></td></tr
><tr
id=sl_svn23_212

><td class="source">92:	lsl	BL<br></td></tr
><tr
id=sl_svn23_213

><td class="source">	rol	BH<br></td></tr
><tr
id=sl_svn23_214

><td class="source">	rol	CL<br></td></tr
><tr
id=sl_svn23_215

><td class="source">	andi	BL, 0b11111000<br></td></tr
><tr
id=sl_svn23_216

><td class="source">	ori	BL, 0b00000101<br></td></tr
><tr
id=sl_svn23_217

><td class="source">	sbrc	T8H, 7<br></td></tr
><tr
id=sl_svn23_218

><td class="source">	subi	BL, 2<br></td></tr
><tr
id=sl_svn23_219

><td class="source">	dec	DH<br></td></tr
><tr
id=sl_svn23_220

><td class="source">	brne	90b<br></td></tr
><tr
id=sl_svn23_221

><td class="source">	lsr	CL<br></td></tr
><tr
id=sl_svn23_222

><td class="source">	ror	BH<br></td></tr
><tr
id=sl_svn23_223

><td class="source">	ror	BL<br></td></tr
><tr
id=sl_svn23_224

><td class="source">	lsr	CL<br></td></tr
><tr
id=sl_svn23_225

><td class="source">	ror	BH<br></td></tr
><tr
id=sl_svn23_226

><td class="source">	ror	BL<br></td></tr
><tr
id=sl_svn23_227

><td class="source">.endm<br></td></tr
><tr
id=sl_svn23_228

><td class="source"><br></td></tr
><tr
id=sl_svn23_229

><td class="source">#endif	/* FFFT_ASM */<br></td></tr
><tr
id=sl_svn23_230

><td class="source"><br></td></tr
><tr
id=sl_svn23_231

><td class="source">#endif	/* FFT_N */<br></td></tr
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
 &nbsp; <a href="/p/neuroelec/source/diff?spec=svn23&r=21&amp;format=side&amp;path=/trunk/libraries/Arduino+1.0/ffft/ffft.h&amp;old_path=/trunk/libraries/Arduino+1.0/ffft/ffft.h&amp;old=">Diff</a>
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
 <a href="https://www.google.com/accounts/ServiceLogin?service=code&amp;ltmpl=phosting&amp;continue=http%3A%2F%2Fcode.google.com%2Fp%2Fneuroelec%2Fsource%2Fbrowse%2Ftrunk%2Flibraries%2FArduino%25201.0%2Fffft%2Fffft.h&amp;followup=http%3A%2F%2Fcode.google.com%2Fp%2Fneuroelec%2Fsource%2Fbrowse%2Ftrunk%2Flibraries%2FArduino%25201.0%2Fffft%2Fffft.h"
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
 
 <a href="/p/neuroelec/source/list?path=/trunk/libraries/Arduino+1.0/ffft/ffft.h&start=21">All revisions of this file</a>
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
 
 <div>Size: 3088 bytes,
 231 lines</div>
 
 <div><a href="//neuroelec.googlecode.com/svn/trunk/libraries/Arduino 1.0/ffft/ffft.h">View raw file</a></div>
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

<script src="http://www.gstatic.com/codesite/ph/16216231599268812631/js/prettify/prettify.js"></script>
<script type="text/javascript">prettyPrint();</script>


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
 var paths = {'svn23': '/trunk/libraries/Arduino 1.0/ffft/ffft.h'}
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

