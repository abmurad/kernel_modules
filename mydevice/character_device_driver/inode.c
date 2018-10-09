<!DOCTYPE html>
<!-- Server: sfn-web-9 -->


    

















<!--[if lt IE 7 ]> <html lang="en" class="no-js ie6"> <![endif]-->
<!--[if IE 7 ]>    <html lang="en" class="no-js ie7"> <![endif]-->
<!--[if IE 8 ]>    <html lang="en" class="no-js ie8"> <![endif]-->
<!--[if IE 9 ]>    <html lang="en" class="no-js ie9"> <![endif]-->
<!--[if (gt IE 9)|!(IE)]>-->
<html lang="en" class="no-js"> <!--<![endif]-->
<head>
    <meta content="text/html; charset=UTF-8" http-equiv="content-type"/>
    <title>
  Ramone Linux / Code.git /
  [d1c10c]
  /fs/ramfs/ramfs/inode.c
</title>
    


<script type="text/javascript">
  var _paq = _paq || [];
  _paq.push(['trackPageView', document.title, {
        dimension1: 'ramonelinux',
        dimension2: 'git'
  }]);
  _paq.push(['enableLinkTracking']);
  (function() {
    var u="//analytics.slashdotmedia.com/";
    _paq.push(['setTrackerUrl', u+'sf.php']);
    _paq.push(['setSiteId', 39]);
    var d=document, g=d.createElement('script'), s=d.getElementsByTagName('script')[0];
    g.type='text/javascript'; g.async=true; g.defer=true; g.src=u+'sf.js'; s.parentNode.insertBefore(g,s);
  })();
</script>
<noscript><p><img src="//analytics.slashdotmedia.com/sf.php?idsite=39" style="border:0;" alt="" /></p></noscript>

<meta id="project_name" name="project_name" content='ramonelinux' />
<!--[if lt IE 7 ]>
  <script src="https://a.fsdn.com/allura/nf/1472496229/_ew_/theme/sftheme/js/sftheme/vendor/dd_belatedpng.js"></script>
  <script> DD_belatedPNG.fix('img, .png_bg'); //fix any <img> or .png_bg background-images </script>
<![endif]-->
<link href='//fonts.googleapis.com/css?family=Ubuntu:regular' rel='stylesheet' type='text/css'>
    
        <!-- ew:head_css -->

    
        <link rel="stylesheet"
                type="text/css"
                href="https://a.fsdn.com/allura/nf/1472496229/_ew_/_slim/css?href=allura%2Fcss%2Fforge%2Fhilite.css%3Ballura%2Fcss%2Fforge%2Ftooltipster.css"
                >
    
        <link rel="stylesheet"
                type="text/css"
                href="https://a.fsdn.com/allura/nf/1472496229/_ew_/allura/css/font-awesome.min.css"
                >
    
        <link rel="stylesheet"
                type="text/css"
                href="https://a.fsdn.com/allura/nf/1472496229/_ew_/theme/sftheme/css/forge.css"
                >
    
        
<!-- /ew:head_css -->

    
    
        <!-- ew:head_js -->

    
        <script type="text/javascript" src="https://a.fsdn.com/allura/nf/1472496229/_ew_/_slim/js?href=allura%2Fjs%2Fjquery-base.js%3Btheme%2Fsftheme%2Fjs%2Fsftheme%2Fvendor%2Fmodernizr.3.3.1.custom.js%3Btheme%2Fsftheme%2Fjs%2Fsftheme%2Fshared_head.js"></script>
    
        
<!-- /ew:head_js -->

    

    
        <style type="text/css">
            #page-body.project---init-- #top_nav { display: none; }

#page-body.project---init-- #nav_menu_holder { display: none; margin-bottom: 0; }

#page-body.project---init-- #content_base {margin-top: 0; }
        </style>
    
    
    <link rel="alternate" type="application/rss+xml" title="RSS" href="/p/ramonelinux/code.git/feed.rss"/>
    <link rel="alternate" type="application/atom+xml" title="Atom" href="/p/ramonelinux/code.git/feed.atom"/>

    <style>.XNSArUxglNfCmPsVXYfrRGWeaQ {
        display: none
    }</style>

    
    
    
    


<script type="text/javascript">
    (function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){
            (i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),
        m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)
    })(window,document,'script','//www.google-analytics.com/analytics.js','ga');

    function _add_tracking(prefix, tracking_id) {
        ga('create', tracking_id, {cookieDomain: 'auto', 'name': prefix});
        
        ga(prefix+'.set', 'dimension9', 'ramonelinux');
        ga(prefix+'.set', 'dimension10', 'git');
        
        ga(prefix+'.set', 'dimension13', 'Logged Out');
        ga(prefix+'.send', 'pageview');
    }
      _add_tracking('sfnt1', 'UA-32013-6');
      _add_tracking('sfnt2', 'UA-36130941-1');
    
</script>
</head>

<body class="" id="forge">

    
        <!-- ew:body_top_js -->

    
        
<!-- /ew:body_top_js -->

    




<header id="site-header">
    <div class="wrapper">
        <a href="/" class="logo">
            <span>SourceForge</span>
        </a>
        
        <form method="get" action="/directory/">
            <input type="text" id="words" name="q" placeholder="Search">
        </form>
        
        <!--Switch to {language}-->
        <nav id="nav-site">
            <a href="/directory/" title="Browse our software.">Browse</a>
            <a href="/directory/enterprise" title="Browse our Enterprise software.">Enterprise</a>
            <a href="/blog/" title="Read the latest news from the SF HQ.">Blog</a>
            <a href="//deals.sourceforge.net/?utm_source=sourceforge&amp;utm_medium=navbar&amp;utm_campaign=homepage" title="Discover and Save on the Best Gear, Gadgets, and Software" class="featured-link" target="_blank">Deals</a>
            <a href="/support" title="Contact us for help and feedback.">Help</a>
            <a href="/create"  class="featured-link blue"  style="" title="Create and publish Open Source software for free.">Create</a>
        </nav>
        <nav id="nav-account">
            
              <div class="logged_out">
                <a href="/auth/">Log In</a>
                <span>or</span>
                <a href="https://sourceforge.net/user/registration/">Join</a>
              </div>
            
        </nav>
    </div>
</header>
<header id="site-sec-header">
    <div class="wrapper">
        <nav id="nav-hubs">
            <h4>Solution Centers</h4>
            <a href="http://goparallel.sourceforge.net/">Go Parallel</a>
        </nav>
        <nav id="nav-collateral">
            <a href="https://library.slashdotmedia.com/">Resources</a>
            <a href="/user/newsletters?source=sfnet_header">Newsletters</a>
            <a href="/cloud-storage-providers/?source=sfnet_header">Cloud Storage Providers</a>
            <a href="/business-voip/?source=sfnet_header">Business VoIP Providers</a>
            
            <a href="/call-center-providers/?source=sfnet_header">Call Center Providers</a>
        </nav>
    </div>
</header>


    
    
    

<section id="page-body" class=" neighborhood-Projects project-ramonelinux mountpoint-code.git">
<div id="nav_menu_holder">
    
        
            



    
    
    
    
    <nav id="breadcrumbs">
        <ul>
            <li itemscope itemtype="http://data-vocabulary.org/Breadcrumb"><a itemprop="url" href="/">Home</a></li>
            <li itemscope itemtype="http://data-vocabulary.org/Breadcrumb"><a itemprop="url" href="/directory">Browse</a></li>
            
            
                
                
            
            
                
            
            
            
                <li itemscope itemtype="http://data-vocabulary.org/Breadcrumb"><a itemprop="url" href="/p/ramonelinux/">Ramone Linux</a></li>
                
            
            
                <li itemscope itemtype="http://data-vocabulary.org/Breadcrumb">Code.git</li>
                
            
        </ul>
    </nav>
    
    
    
  
    
      <img src="/p/ramonelinux/icon?2013-09-18 07:50:46+00:00" class="project_icon" alt="Project Logo">
    
        <h1 class="project_title">
            <a href="/p/ramonelinux/" class="project_link">Ramone Linux</a>
        </h1>
    
    
    
    <span id="dev-status" class="beta">beta</span>
    
    <h2 class="project_summary with-icon">
        A DIY Linux distribution
    </h2>
    
    <div class="brought-by with-icon">
        Brought to you by:
        
        
            
                <a href="/u/geliangtang/">geliangtang</a>
            </div>
    

        
    
</div>
    <div id="top_nav" class="">
        
            
<div id="top_nav_admin">
<ul class="dropdown">
  
    <li class="">
        <a href="/projects/ramonelinux/" class="tool-summary-32">
            Summary
        </a>
        
        
    </li>
  
    <li class="">
        <a href="/projects/ramonelinux/files/" class="tool-files-32">
            Files
        </a>
        
        
    </li>
  
    <li class="">
        <a href="/projects/ramonelinux/reviews" class="tool-reviews-32">
            Reviews
        </a>
        
        
    </li>
  
    <li class="">
        <a href="/projects/ramonelinux/support" class="tool-support-32">
            Support
        </a>
        
        
    </li>
  
    <li class="">
        <a href="/p/ramonelinux/wiki/" class="tool-wiki-32">
            Wiki
        </a>
        
        
    </li>
  
    <li class="">
        <a href="/p/ramonelinux/tickets/" class="tool-tickets-32">
            Tickets
        </a>
        
        
    </li>
  
    <li class="">
        <a href="/p/ramonelinux/discussion/" class="tool-discussion-32">
            Discussion
        </a>
        
        
    </li>
  
    <li class="">
        <a href="/p/ramonelinux/blog/" class="tool-blog-32">
            Blog
        </a>
        
        
    </li>
  
    <li class="">
        <a href="/p/ramonelinux/code-0/" class="tool-svn-32">
            Code
        </a>
        
        
    </li>
  
    <li class="selected">
        <a href="/p/ramonelinux/code.git/" class="tool-git-32">
            Code.git
        </a>
        
        
    </li>
  
  
</ul>
</div>


        
    </div>
    <div id="content_base">
        
            
                
                    


<div id="sidebar">
  
    <div>&nbsp;</div>
  
    
    
      
      
        
    
      <ul class="sidebarmenu">
      
    
  <li>
      
        <a class="icon" href="/p/ramonelinux/code.git/commit_browser" title="Browse Commits"><i class="fa fa-list"></i>
      
      <span>Browse Commits</span>
      </a>
  </li>
  
      
        
    
  <li>
      
        <a class="icon" href="/p/ramonelinux/code.git/fork" title="Fork"><i class="fa fa-code-fork"></i>
      
      <span>Fork</span>
      </a>
  </li>
  
      
        
    
  <li>
      
        <a href="/p/ramonelinux/code.git/merge-requests/"  >
      
      <span class="has_small">Merge Requests</span>
      <small>0</small></a>
  </li>
  
      
        
    
      </ul>
      
    
    
      <h3 class="">Branches</h3>
    
  
      
        
    
      <ul class="sidebarmenu">
      
    
  <li>
      
        <a href="/p/ramonelinux/code.git/ci/master/tree/"  >
      
      <span>master</span>
      </a>
  </li>
  
      
    
    
      </ul>
      
    
    
</div>
                
                
            
            
                
            
            <div class="grid-20 pad">
                <h2 class="dark title">
<a href="/p/ramonelinux/code.git/ci/d1c10c0a4eb8a2af577f694efdaeeac174f1a0f3/">[d1c10c]</a>:

  
  
    <a href="./../../">fs</a> /
    
  
    <a href="./../">ramfs</a> /
    
  
    <a href="./">ramfs</a> /
    
  
 inode.c

                    <!-- actions -->
                    <small>
                        

    
    <a class="icon" href="#" id="maximize-content" title="Maximize"><i class="fa fa-expand"></i>&nbsp;Maximize</a>
    <a class="icon" href="#" id="restore-content" title="Restore"><i class="fa fa-compress"></i>&nbsp;Restore</a>
<a class="icon" href="/p/ramonelinux/code.git/ci/d1c10c0a4eb8a2af577f694efdaeeac174f1a0f3/log/?path=/fs/ramfs/ramfs/inode.c" title="History"><i class="fa fa-calendar"></i>&nbsp;History</a>

                    </small>
                    <!-- /actions -->
                </h2>
                
                <div>
                    
  

                    
  
    <p><a href="?format=raw">Download this file</a></p>
    <div class="clip grid-19 codebrowser">
      <h3>
        177 lines (149 with data), 4.3 kB
      </h3>
      
        <table class="codehilitetable"><tr><td class="linenos"><div class="linenodiv"><pre>  1
  2
  3
  4
  5
  6
  7
  8
  9
 10
 11
 12
 13
 14
 15
 16
 17
 18
 19
 20
 21
 22
 23
 24
 25
 26
 27
 28
 29
 30
 31
 32
 33
 34
 35
 36
 37
 38
 39
 40
 41
 42
 43
 44
 45
 46
 47
 48
 49
 50
 51
 52
 53
 54
 55
 56
 57
 58
 59
 60
 61
 62
 63
 64
 65
 66
 67
 68
 69
 70
 71
 72
 73
 74
 75
 76
 77
 78
 79
 80
 81
 82
 83
 84
 85
 86
 87
 88
 89
 90
 91
 92
 93
 94
 95
 96
 97
 98
 99
100
101
102
103
104
105
106
107
108
109
110
111
112
113
114
115
116
117
118
119
120
121
122
123
124
125
126
127
128
129
130
131
132
133
134
135
136
137
138
139
140
141
142
143
144
145
146
147
148
149
150
151
152
153
154
155
156
157
158
159
160
161
162
163
164
165
166
167
168
169
170
171
172
173
174
175
176</pre></div></td><td class="code"><div class="codehilite"><pre><div id="l1" class="code_block"><span class="cp">#include &lt;linux/fs.h&gt;</span>
</div><div id="l2" class="code_block"><span class="cp">#include &lt;linux/pagemap.h&gt;</span>
</div><div id="l3" class="code_block"><span class="cp">#include &lt;linux/init.h&gt;</span>
</div><div id="l4" class="code_block"><span class="cp">#include &lt;linux/magic.h&gt;</span>
</div><div id="l5" class="code_block"><span class="cp">#include &lt;linux/slab.h&gt;</span>
</div><div id="l6" class="code_block">
</div><div id="l7" class="code_block"><span class="k">static</span> <span class="k">const</span> <span class="k">struct</span> <span class="n">inode_operations</span> <span class="n">ramfs_dir_inode_operations</span><span class="p">;</span>
</div><div id="l8" class="code_block">
</div><div id="l9" class="code_block"><span class="k">const</span> <span class="k">struct</span> <span class="n">address_space_operations</span> <span class="n">ramfs_aops</span> <span class="o">=</span> <span class="p">{</span>
</div><div id="l10" class="code_block">	<span class="p">.</span><span class="n">readpage</span>	<span class="o">=</span> <span class="n">simple_readpage</span><span class="p">,</span>
</div><div id="l11" class="code_block">	<span class="p">.</span><span class="n">write_begin</span>	<span class="o">=</span> <span class="n">simple_write_begin</span><span class="p">,</span>
</div><div id="l12" class="code_block">	<span class="p">.</span><span class="n">write_end</span>	<span class="o">=</span> <span class="n">simple_write_end</span><span class="p">,</span>
</div><div id="l13" class="code_block"><span class="p">};</span>
</div><div id="l14" class="code_block">
</div><div id="l15" class="code_block"><span class="k">const</span> <span class="k">struct</span> <span class="n">file_operations</span> <span class="n">ramfs_file_operations</span> <span class="o">=</span> <span class="p">{</span>
</div><div id="l16" class="code_block">	<span class="p">.</span><span class="n">read</span>           <span class="o">=</span> <span class="n">new_sync_read</span><span class="p">,</span>
</div><div id="l17" class="code_block">	<span class="p">.</span><span class="n">read_iter</span>      <span class="o">=</span> <span class="n">generic_file_read_iter</span><span class="p">,</span>
</div><div id="l18" class="code_block">	<span class="p">.</span><span class="n">write</span>          <span class="o">=</span> <span class="n">new_sync_write</span><span class="p">,</span>
</div><div id="l19" class="code_block">	<span class="p">.</span><span class="n">write_iter</span>     <span class="o">=</span> <span class="n">generic_file_write_iter</span><span class="p">,</span>
</div><div id="l20" class="code_block">	<span class="p">.</span><span class="n">mmap</span>           <span class="o">=</span> <span class="n">generic_file_mmap</span><span class="p">,</span>
</div><div id="l21" class="code_block">	<span class="p">.</span><span class="n">fsync</span>          <span class="o">=</span> <span class="n">noop_fsync</span><span class="p">,</span>
</div><div id="l22" class="code_block">	<span class="p">.</span><span class="n">splice_read</span>    <span class="o">=</span> <span class="n">generic_file_splice_read</span><span class="p">,</span>
</div><div id="l23" class="code_block">	<span class="p">.</span><span class="n">splice_write</span>   <span class="o">=</span> <span class="n">iter_file_splice_write</span><span class="p">,</span>
</div><div id="l24" class="code_block">	<span class="p">.</span><span class="n">llseek</span>         <span class="o">=</span> <span class="n">generic_file_llseek</span><span class="p">,</span>
</div><div id="l25" class="code_block"><span class="p">};</span>
</div><div id="l26" class="code_block">
</div><div id="l27" class="code_block"><span class="k">const</span> <span class="k">struct</span> <span class="n">inode_operations</span> <span class="n">ramfs_file_inode_operations</span> <span class="o">=</span> <span class="p">{</span>
</div><div id="l28" class="code_block">	<span class="p">.</span><span class="n">setattr</span>	<span class="o">=</span> <span class="n">simple_setattr</span><span class="p">,</span>
</div><div id="l29" class="code_block">	<span class="p">.</span><span class="n">getattr</span>	<span class="o">=</span> <span class="n">simple_getattr</span><span class="p">,</span>
</div><div id="l30" class="code_block"><span class="p">};</span>
</div><div id="l31" class="code_block">
</div><div id="l32" class="code_block"><span class="k">struct</span> <span class="n">inode</span> <span class="o">*</span><span class="nf">ramfs_get_inode</span><span class="p">(</span><span class="k">struct</span> <span class="n">super_block</span> <span class="o">*</span><span class="n">sb</span><span class="p">,</span>
</div><div id="l33" class="code_block">				<span class="k">const</span> <span class="k">struct</span> <span class="n">inode</span> <span class="o">*</span><span class="n">dir</span><span class="p">,</span> <span class="kt">umode_t</span> <span class="n">mode</span><span class="p">,</span> <span class="kt">dev_t</span> <span class="n">dev</span><span class="p">)</span>
</div><div id="l34" class="code_block"><span class="p">{</span>
</div><div id="l35" class="code_block">	<span class="k">struct</span> <span class="n">inode</span> <span class="o">*</span> <span class="n">inode</span> <span class="o">=</span> <span class="n">new_inode</span><span class="p">(</span><span class="n">sb</span><span class="p">);</span>
</div><div id="l36" class="code_block">
</div><div id="l37" class="code_block">	<span class="k">if</span> <span class="p">(</span><span class="n">inode</span><span class="p">)</span> <span class="p">{</span>
</div><div id="l38" class="code_block">		<span class="n">inode</span><span class="o">-&gt;</span><span class="n">i_ino</span> <span class="o">=</span> <span class="n">get_next_ino</span><span class="p">();</span>
</div><div id="l39" class="code_block">		<span class="n">inode_init_owner</span><span class="p">(</span><span class="n">inode</span><span class="p">,</span> <span class="n">dir</span><span class="p">,</span> <span class="n">mode</span><span class="p">);</span>
</div><div id="l40" class="code_block">		<span class="n">inode</span><span class="o">-&gt;</span><span class="n">i_mapping</span><span class="o">-&gt;</span><span class="n">a_ops</span> <span class="o">=</span> <span class="o">&amp;</span><span class="n">ramfs_aops</span><span class="p">;</span>
</div><div id="l41" class="code_block">		<span class="n">mapping_set_gfp_mask</span><span class="p">(</span><span class="n">inode</span><span class="o">-&gt;</span><span class="n">i_mapping</span><span class="p">,</span> <span class="n">GFP_HIGHUSER</span><span class="p">);</span>
</div><div id="l42" class="code_block">		<span class="n">mapping_set_unevictable</span><span class="p">(</span><span class="n">inode</span><span class="o">-&gt;</span><span class="n">i_mapping</span><span class="p">);</span>
</div><div id="l43" class="code_block">		<span class="n">inode</span><span class="o">-&gt;</span><span class="n">i_atime</span> <span class="o">=</span> <span class="n">inode</span><span class="o">-&gt;</span><span class="n">i_mtime</span> <span class="o">=</span> <span class="n">inode</span><span class="o">-&gt;</span><span class="n">i_ctime</span> <span class="o">=</span> <span class="n">CURRENT_TIME</span><span class="p">;</span>
</div><div id="l44" class="code_block">		<span class="k">switch</span> <span class="p">(</span><span class="n">mode</span> <span class="o">&amp;</span> <span class="n">S_IFMT</span><span class="p">)</span> <span class="p">{</span>
</div><div id="l45" class="code_block">		<span class="k">default</span><span class="o">:</span>
</div><div id="l46" class="code_block">			<span class="n">init_special_inode</span><span class="p">(</span><span class="n">inode</span><span class="p">,</span> <span class="n">mode</span><span class="p">,</span> <span class="n">dev</span><span class="p">);</span>
</div><div id="l47" class="code_block">			<span class="k">break</span><span class="p">;</span>
</div><div id="l48" class="code_block">		<span class="k">case</span> <span class="nl">S_IFREG</span><span class="p">:</span>
</div><div id="l49" class="code_block">			<span class="n">inode</span><span class="o">-&gt;</span><span class="n">i_op</span> <span class="o">=</span> <span class="o">&amp;</span><span class="n">ramfs_file_inode_operations</span><span class="p">;</span>
</div><div id="l50" class="code_block">			<span class="n">inode</span><span class="o">-&gt;</span><span class="n">i_fop</span> <span class="o">=</span> <span class="o">&amp;</span><span class="n">ramfs_file_operations</span><span class="p">;</span>
</div><div id="l51" class="code_block">			<span class="k">break</span><span class="p">;</span>
</div><div id="l52" class="code_block">		<span class="k">case</span> <span class="nl">S_IFDIR</span><span class="p">:</span>
</div><div id="l53" class="code_block">			<span class="n">inode</span><span class="o">-&gt;</span><span class="n">i_op</span> <span class="o">=</span> <span class="o">&amp;</span><span class="n">ramfs_dir_inode_operations</span><span class="p">;</span>
</div><div id="l54" class="code_block">			<span class="n">inode</span><span class="o">-&gt;</span><span class="n">i_fop</span> <span class="o">=</span> <span class="o">&amp;</span><span class="n">simple_dir_operations</span><span class="p">;</span>
</div><div id="l55" class="code_block">			<span class="k">break</span><span class="p">;</span>
</div><div id="l56" class="code_block">		<span class="p">}</span>
</div><div id="l57" class="code_block">	<span class="p">}</span>
</div><div id="l58" class="code_block">	<span class="k">return</span> <span class="n">inode</span><span class="p">;</span>
</div><div id="l59" class="code_block"><span class="p">}</span>
</div><div id="l60" class="code_block">
</div><div id="l61" class="code_block"><span class="cm">/*</span>
</div><div id="l62" class="code_block"><span class="cm"> * File creation. Allocate an inode, and we&#39;re done..</span>
</div><div id="l63" class="code_block"><span class="cm"> */</span>
</div><div id="l64" class="code_block"><span class="cm">/* SMP-safe */</span>
</div><div id="l65" class="code_block"><span class="k">static</span> <span class="kt">int</span>
</div><div id="l66" class="code_block"><span class="nf">ramfs_mknod</span><span class="p">(</span><span class="k">struct</span> <span class="n">inode</span> <span class="o">*</span><span class="n">dir</span><span class="p">,</span> <span class="k">struct</span> <span class="n">dentry</span> <span class="o">*</span><span class="n">dentry</span><span class="p">,</span> <span class="kt">umode_t</span> <span class="n">mode</span><span class="p">,</span> <span class="kt">dev_t</span> <span class="n">dev</span><span class="p">)</span>
</div><div id="l67" class="code_block"><span class="p">{</span>
</div><div id="l68" class="code_block">	<span class="k">struct</span> <span class="n">inode</span> <span class="o">*</span> <span class="n">inode</span> <span class="o">=</span> <span class="n">ramfs_get_inode</span><span class="p">(</span><span class="n">dir</span><span class="o">-&gt;</span><span class="n">i_sb</span><span class="p">,</span> <span class="n">dir</span><span class="p">,</span> <span class="n">mode</span><span class="p">,</span> <span class="n">dev</span><span class="p">);</span>
</div><div id="l69" class="code_block">	<span class="kt">int</span> <span class="n">error</span> <span class="o">=</span> <span class="o">-</span><span class="n">ENOSPC</span><span class="p">;</span>
</div><div id="l70" class="code_block">
</div><div id="l71" class="code_block">	<span class="k">if</span> <span class="p">(</span><span class="n">inode</span><span class="p">)</span> <span class="p">{</span>
</div><div id="l72" class="code_block">		<span class="n">d_instantiate</span><span class="p">(</span><span class="n">dentry</span><span class="p">,</span> <span class="n">inode</span><span class="p">);</span>
</div><div id="l73" class="code_block">		<span class="n">dget</span><span class="p">(</span><span class="n">dentry</span><span class="p">);</span>	<span class="cm">/* Extra count - pin the dentry in core */</span>
</div><div id="l74" class="code_block">		<span class="n">error</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span>
</div><div id="l75" class="code_block">		<span class="n">dir</span><span class="o">-&gt;</span><span class="n">i_mtime</span> <span class="o">=</span> <span class="n">dir</span><span class="o">-&gt;</span><span class="n">i_ctime</span> <span class="o">=</span> <span class="n">CURRENT_TIME</span><span class="p">;</span>
</div><div id="l76" class="code_block">	<span class="p">}</span>
</div><div id="l77" class="code_block">	<span class="k">return</span> <span class="n">error</span><span class="p">;</span>
</div><div id="l78" class="code_block"><span class="p">}</span>
</div><div id="l79" class="code_block">
</div><div id="l80" class="code_block"><span class="k">static</span> <span class="kt">int</span> <span class="nf">ramfs_mkdir</span><span class="p">(</span><span class="k">struct</span> <span class="n">inode</span> <span class="o">*</span> <span class="n">dir</span><span class="p">,</span> <span class="k">struct</span> <span class="n">dentry</span> <span class="o">*</span> <span class="n">dentry</span><span class="p">,</span> <span class="kt">umode_t</span> <span class="n">mode</span><span class="p">)</span>
</div><div id="l81" class="code_block"><span class="p">{</span>
</div><div id="l82" class="code_block">	<span class="k">return</span> <span class="n">ramfs_mknod</span><span class="p">(</span><span class="n">dir</span><span class="p">,</span> <span class="n">dentry</span><span class="p">,</span> <span class="n">mode</span> <span class="o">|</span> <span class="n">S_IFDIR</span><span class="p">,</span> <span class="mi">0</span><span class="p">);</span>
</div><div id="l83" class="code_block"><span class="p">}</span>
</div><div id="l84" class="code_block">
</div><div id="l85" class="code_block"><span class="k">static</span> <span class="kt">int</span> <span class="nf">ramfs_create</span><span class="p">(</span><span class="k">struct</span> <span class="n">inode</span> <span class="o">*</span><span class="n">dir</span><span class="p">,</span> <span class="k">struct</span> <span class="n">dentry</span> <span class="o">*</span><span class="n">dentry</span><span class="p">,</span> <span class="kt">umode_t</span> <span class="n">mode</span><span class="p">,</span> <span class="kt">bool</span> <span class="n">excl</span><span class="p">)</span>
</div><div id="l86" class="code_block"><span class="p">{</span>
</div><div id="l87" class="code_block">	<span class="k">return</span> <span class="n">ramfs_mknod</span><span class="p">(</span><span class="n">dir</span><span class="p">,</span> <span class="n">dentry</span><span class="p">,</span> <span class="n">mode</span> <span class="o">|</span> <span class="n">S_IFREG</span><span class="p">,</span> <span class="mi">0</span><span class="p">);</span>
</div><div id="l88" class="code_block"><span class="p">}</span>
</div><div id="l89" class="code_block">
</div><div id="l90" class="code_block"><span class="k">static</span> <span class="k">const</span> <span class="k">struct</span> <span class="n">inode_operations</span> <span class="n">ramfs_dir_inode_operations</span> <span class="o">=</span> <span class="p">{</span>
</div><div id="l91" class="code_block">	<span class="p">.</span><span class="n">create</span>		<span class="o">=</span> <span class="n">ramfs_create</span><span class="p">,</span>
</div><div id="l92" class="code_block">	<span class="p">.</span><span class="n">lookup</span>		<span class="o">=</span> <span class="n">simple_lookup</span><span class="p">,</span>
</div><div id="l93" class="code_block">	<span class="p">.</span><span class="n">link</span>		<span class="o">=</span> <span class="n">simple_link</span><span class="p">,</span>
</div><div id="l94" class="code_block">	<span class="p">.</span><span class="n">unlink</span>		<span class="o">=</span> <span class="n">simple_unlink</span><span class="p">,</span>
</div><div id="l95" class="code_block">	<span class="p">.</span><span class="n">mkdir</span>		<span class="o">=</span> <span class="n">ramfs_mkdir</span><span class="p">,</span>
</div><div id="l96" class="code_block">	<span class="p">.</span><span class="n">rmdir</span>		<span class="o">=</span> <span class="n">simple_rmdir</span><span class="p">,</span>
</div><div id="l97" class="code_block">	<span class="p">.</span><span class="n">mknod</span>		<span class="o">=</span> <span class="n">ramfs_mknod</span><span class="p">,</span>
</div><div id="l98" class="code_block">	<span class="p">.</span><span class="n">rename</span>		<span class="o">=</span> <span class="n">simple_rename</span><span class="p">,</span>
</div><div id="l99" class="code_block"><span class="p">};</span>
</div><div id="l100" class="code_block">
</div><div id="l101" class="code_block"><span class="k">static</span> <span class="k">const</span> <span class="k">struct</span> <span class="n">super_operations</span> <span class="n">ramfs_ops</span> <span class="o">=</span> <span class="p">{</span>
</div><div id="l102" class="code_block">	<span class="p">.</span><span class="n">statfs</span>		<span class="o">=</span> <span class="n">simple_statfs</span><span class="p">,</span>
</div><div id="l103" class="code_block">	<span class="p">.</span><span class="n">drop_inode</span>	<span class="o">=</span> <span class="n">generic_delete_inode</span><span class="p">,</span>
</div><div id="l104" class="code_block">	<span class="p">.</span><span class="n">show_options</span>	<span class="o">=</span> <span class="n">generic_show_options</span><span class="p">,</span>
</div><div id="l105" class="code_block"><span class="p">};</span>
</div><div id="l106" class="code_block">
</div><div id="l107" class="code_block"><span class="k">struct</span> <span class="n">ramfs_mount_opts</span> <span class="p">{</span>
</div><div id="l108" class="code_block">	<span class="kt">umode_t</span> <span class="n">mode</span><span class="p">;</span>
</div><div id="l109" class="code_block"><span class="p">};</span>
</div><div id="l110" class="code_block">
</div><div id="l111" class="code_block"><span class="k">struct</span> <span class="n">ramfs_fs_info</span> <span class="p">{</span>
</div><div id="l112" class="code_block">	<span class="k">struct</span> <span class="n">ramfs_mount_opts</span> <span class="n">mount_opts</span><span class="p">;</span>
</div><div id="l113" class="code_block"><span class="p">};</span>
</div><div id="l114" class="code_block">
</div><div id="l115" class="code_block"><span class="kt">int</span> <span class="nf">ramfs_fill_super</span><span class="p">(</span><span class="k">struct</span> <span class="n">super_block</span> <span class="o">*</span><span class="n">sb</span><span class="p">,</span> <span class="kt">void</span> <span class="o">*</span><span class="n">data</span><span class="p">,</span> <span class="kt">int</span> <span class="n">silent</span><span class="p">)</span>
</div><div id="l116" class="code_block"><span class="p">{</span>
</div><div id="l117" class="code_block">	<span class="k">struct</span> <span class="n">ramfs_fs_info</span> <span class="o">*</span><span class="n">fsi</span><span class="p">;</span>
</div><div id="l118" class="code_block">	<span class="k">struct</span> <span class="n">inode</span> <span class="o">*</span><span class="n">inode</span><span class="p">;</span>
</div><div id="l119" class="code_block">
</div><div id="l120" class="code_block">	<span class="n">save_mount_options</span><span class="p">(</span><span class="n">sb</span><span class="p">,</span> <span class="n">data</span><span class="p">);</span>
</div><div id="l121" class="code_block">
</div><div id="l122" class="code_block">	<span class="n">fsi</span> <span class="o">=</span> <span class="n">kzalloc</span><span class="p">(</span><span class="k">sizeof</span><span class="p">(</span><span class="k">struct</span> <span class="n">ramfs_fs_info</span><span class="p">),</span> <span class="n">GFP_KERNEL</span><span class="p">);</span>
</div><div id="l123" class="code_block">	<span class="n">sb</span><span class="o">-&gt;</span><span class="n">s_fs_info</span> <span class="o">=</span> <span class="n">fsi</span><span class="p">;</span>
</div><div id="l124" class="code_block">	<span class="k">if</span> <span class="p">(</span><span class="o">!</span><span class="n">fsi</span><span class="p">)</span>
</div><div id="l125" class="code_block">		<span class="k">return</span> <span class="o">-</span><span class="n">ENOMEM</span><span class="p">;</span>
</div><div id="l126" class="code_block">
</div><div id="l127" class="code_block">	<span class="n">sb</span><span class="o">-&gt;</span><span class="n">s_maxbytes</span>		<span class="o">=</span> <span class="n">MAX_LFS_FILESIZE</span><span class="p">;</span>
</div><div id="l128" class="code_block">	<span class="n">sb</span><span class="o">-&gt;</span><span class="n">s_blocksize</span>		<span class="o">=</span> <span class="n">PAGE_CACHE_SIZE</span><span class="p">;</span>
</div><div id="l129" class="code_block">	<span class="n">sb</span><span class="o">-&gt;</span><span class="n">s_blocksize_bits</span>	<span class="o">=</span> <span class="n">PAGE_CACHE_SHIFT</span><span class="p">;</span>
</div><div id="l130" class="code_block">	<span class="n">sb</span><span class="o">-&gt;</span><span class="n">s_magic</span>		<span class="o">=</span> <span class="n">RAMFS_MAGIC</span><span class="p">;</span>
</div><div id="l131" class="code_block">	<span class="n">sb</span><span class="o">-&gt;</span><span class="n">s_op</span>		<span class="o">=</span> <span class="o">&amp;</span><span class="n">ramfs_ops</span><span class="p">;</span>
</div><div id="l132" class="code_block">	<span class="n">sb</span><span class="o">-&gt;</span><span class="n">s_time_gran</span>		<span class="o">=</span> <span class="mi">1</span><span class="p">;</span>
</div><div id="l133" class="code_block">
</div><div id="l134" class="code_block">	<span class="n">inode</span> <span class="o">=</span> <span class="n">ramfs_get_inode</span><span class="p">(</span><span class="n">sb</span><span class="p">,</span> <span class="nb">NULL</span><span class="p">,</span> <span class="n">S_IFDIR</span> <span class="o">|</span> <span class="n">fsi</span><span class="o">-&gt;</span><span class="n">mount_opts</span><span class="p">.</span><span class="n">mode</span><span class="p">,</span> <span class="mi">0</span><span class="p">);</span>
</div><div id="l135" class="code_block">	<span class="n">sb</span><span class="o">-&gt;</span><span class="n">s_root</span> <span class="o">=</span> <span class="n">d_make_root</span><span class="p">(</span><span class="n">inode</span><span class="p">);</span>
</div><div id="l136" class="code_block">	<span class="k">if</span> <span class="p">(</span><span class="o">!</span><span class="n">sb</span><span class="o">-&gt;</span><span class="n">s_root</span><span class="p">)</span>
</div><div id="l137" class="code_block">		<span class="k">return</span> <span class="o">-</span><span class="n">ENOMEM</span><span class="p">;</span>
</div><div id="l138" class="code_block">
</div><div id="l139" class="code_block">	<span class="k">return</span> <span class="mi">0</span><span class="p">;</span>
</div><div id="l140" class="code_block"><span class="p">}</span>
</div><div id="l141" class="code_block">
</div><div id="l142" class="code_block"><span class="k">struct</span> <span class="n">dentry</span> <span class="o">*</span><span class="nf">ramfs_mount</span><span class="p">(</span><span class="k">struct</span> <span class="n">file_system_type</span> <span class="o">*</span><span class="n">fs_type</span><span class="p">,</span>
</div><div id="l143" class="code_block">	<span class="kt">int</span> <span class="n">flags</span><span class="p">,</span> <span class="k">const</span> <span class="kt">char</span> <span class="o">*</span><span class="n">dev_name</span><span class="p">,</span> <span class="kt">void</span> <span class="o">*</span><span class="n">data</span><span class="p">)</span>
</div><div id="l144" class="code_block"><span class="p">{</span>
</div><div id="l145" class="code_block">	<span class="k">return</span> <span class="n">mount_nodev</span><span class="p">(</span><span class="n">fs_type</span><span class="p">,</span> <span class="n">flags</span><span class="p">,</span> <span class="n">data</span><span class="p">,</span> <span class="n">ramfs_fill_super</span><span class="p">);</span>
</div><div id="l146" class="code_block"><span class="p">}</span>
</div><div id="l147" class="code_block">
</div><div id="l148" class="code_block"><span class="k">static</span> <span class="kt">void</span> <span class="nf">ramfs_kill_sb</span><span class="p">(</span><span class="k">struct</span> <span class="n">super_block</span> <span class="o">*</span><span class="n">sb</span><span class="p">)</span>
</div><div id="l149" class="code_block"><span class="p">{</span>
</div><div id="l150" class="code_block">	<span class="n">kfree</span><span class="p">(</span><span class="n">sb</span><span class="o">-&gt;</span><span class="n">s_fs_info</span><span class="p">);</span>
</div><div id="l151" class="code_block">	<span class="n">kill_litter_super</span><span class="p">(</span><span class="n">sb</span><span class="p">);</span>
</div><div id="l152" class="code_block"><span class="p">}</span>
</div><div id="l153" class="code_block">
</div><div id="l154" class="code_block"><span class="k">static</span> <span class="k">struct</span> <span class="n">file_system_type</span> <span class="n">ramfs_fs_type</span> <span class="o">=</span> <span class="p">{</span>
</div><div id="l155" class="code_block">	<span class="p">.</span><span class="n">name</span>		<span class="o">=</span> <span class="s">&quot;reramfs&quot;</span><span class="p">,</span>
</div><div id="l156" class="code_block">	<span class="p">.</span><span class="n">mount</span>		<span class="o">=</span> <span class="n">ramfs_mount</span><span class="p">,</span>
</div><div id="l157" class="code_block">	<span class="p">.</span><span class="n">kill_sb</span>	<span class="o">=</span> <span class="n">ramfs_kill_sb</span><span class="p">,</span>
</div><div id="l158" class="code_block">	<span class="p">.</span><span class="n">fs_flags</span>	<span class="o">=</span> <span class="n">FS_USERNS_MOUNT</span><span class="p">,</span>
</div><div id="l159" class="code_block"><span class="p">};</span>
</div><div id="l160" class="code_block">
</div><div id="l161" class="code_block"><span class="k">static</span> <span class="kt">int</span> <span class="n">__init</span> <span class="nf">ramfs_fs_init</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span>
</div><div id="l162" class="code_block"><span class="p">{</span>
</div><div id="l163" class="code_block">	<span class="k">static</span> <span class="kt">unsigned</span> <span class="kt">long</span> <span class="n">once</span><span class="p">;</span>
</div><div id="l164" class="code_block">
</div><div id="l165" class="code_block">	<span class="k">if</span> <span class="p">(</span><span class="n">test_and_set_bit</span><span class="p">(</span><span class="mi">0</span><span class="p">,</span> <span class="o">&amp;</span><span class="n">once</span><span class="p">))</span>
</div><div id="l166" class="code_block">		<span class="k">return</span> <span class="mi">0</span><span class="p">;</span>
</div><div id="l167" class="code_block">	<span class="k">return</span> <span class="n">register_filesystem</span><span class="p">(</span><span class="o">&amp;</span><span class="n">ramfs_fs_type</span><span class="p">);</span>
</div><div id="l168" class="code_block"><span class="p">}</span>
</div><div id="l169" class="code_block">
</div><div id="l170" class="code_block"><span class="k">static</span> <span class="kt">void</span> <span class="n">__exit</span> <span class="nf">ramfs_fs_exit</span><span class="p">(</span><span class="kt">void</span><span class="p">)</span>
</div><div id="l171" class="code_block"><span class="p">{</span>
</div><div id="l172" class="code_block">    <span class="n">unregister_filesystem</span><span class="p">(</span><span class="o">&amp;</span><span class="n">ramfs_fs_type</span><span class="p">);</span>
</div><div id="l173" class="code_block"><span class="p">}</span>
</div><div id="l174" class="code_block">
</div><div id="l175" class="code_block"><span class="n">module_init</span><span class="p">(</span><span class="n">ramfs_fs_init</span><span class="p">);</span>
</div><div id="l176" class="code_block"><span class="n">module_exit</span><span class="p">(</span><span class="n">ramfs_fs_exit</span><span class="p">);</span>
</div></pre></div>
</td></tr></table>
      
    </div>
  

                </div>
                
                
            </div>
        
    </div>
</section>
  


<footer id="site-footer">
    <div class="wrapper">
<nav>
            <h5>SourceForge</h5>
            <a href="/about">About</a>
            <a href="/blog/category/sitestatus/">Site Status</a>
            <a href="http://twitter.com/sfnet_ops">@sfnet_ops</a>
            <a id="allura-notice" href="http://allura.apache.org/">
                <p>Powered by</p>
                <p>Apache Allura™</p>
                <img src="https://a.fsdn.com/allura/nf/1472496229/_ew_/theme/sftheme/images/sftheme/logo-black-svg_g.png" />
            </a>
        </nav>
        <nav>
            <h5>Find and Develop Software</h5>
            <a href="/create/">Create a Project</a>
            <a href="/directory/">Software Directory</a>
            <a href="/top">Top Downloaded Projects</a>
        </nav>
        <nav>
            <h5>Community</h5>
            <a href="/blog/">Blog</a>
            <a href="http://twitter.com/sourceforge">@sourceforge</a>
            <a href="https://library.slashdotmedia.com/">Resources</a>
        </nav>
        <nav>
            <h5>Help</h5>
            <a href="http://p.sf.net/sourceforge/docs">Site Documentation</a>
            <a href="/support">Support Request</a>
        </nav>
    </div>
</footer>
<footer id="site-copyright-footer">
    <div class="wrapper">
        <div id="copyright">
            &copy; 2016 Slashdot Media. All Rights Reserved.<br />
        </div>
        <nav>
            <a href="http://slashdotmedia.com/terms-of-use">Terms</a>
            <a href="http://slashdotmedia.com/privacy-statement/">Privacy</a>
            <span id='teconsent'></span>
            <a href="http://slashdotmedia.com/opt-out-choices">Opt Out Choices</a>
            <a href="http://slashdotmedia.com">Advertise</a>
        </nav>
    </div>
</footer>



    
<div id="newsletter-floating" class="goth-form">
    <h2>Get latest updates about Open Source Projects, Conferences and News.</h2>
    <p>Sign up for the SourceForge newsletter:</p>
    
<form action="/user/newsletters/subscribe" method="post">
    <div class="form">
        <input type="email" name="XLB0clE104U82xOcYUGaDBnERXQ8"  placeholder="email@address.com" value="">
    <input type="submit" value="Subscribe" class="bt">
    </div>
    <div class="fielderror"></div>

    <p class="details">
    <span class="fielderror"></span>
    <label>
        <input type="checkbox" required name="XLhsem1d9sXQwHGgMo7oOw5tuHAU" value="true" checked>I agree to receive quotes, newsletters and other information from sourceforge.net and its partners regarding IT services and products. I understand that I can withdraw my consent at any time. Please refer to our <a href="https://slashdotmedia.com/privacy-statement/">Privacy Policy</a> or <a href="/support">Contact Us</a> for more details
        <input type="hidden" name="XJBYUkEBrgGNhPSP-ek1002pjiGM" value="true">
    </label>
    </p>

    <input type="hidden" name="source" value="floating">
    <input type="hidden" name="XJRsegEpsrXlRMD__cQcFpMVDvKQ" value="IN">
    <input type="hidden" name="XOhsegEpsrXlRMD__cWY58yeGXIU" value="ip_address">
    <input type="hidden" name="XIhYUgld0unR6NiLoKnZyC-V3e78" value="sitewide">
    <input type="hidden" name="XIhYUgld0unR6NiLoKnZyC-V3e78" value="research">
    <input type="hidden" name="XIhYUgld0unR6NiLoKnZyC-V3e78" value="events">
    <input type="hidden" name="XIhYUgld0unR6NiLoKnZyC-V3e78" value="thirdparty">
    <input type="hidden" name="XIhYUgld0unR6NiLoKnZyC-V3e78" value="all">
    <input type="hidden" name="XKhMcgBpX55e50BTE3aNpeTAbWDU" value="">
    
  <input type="hidden" name="_visit_cookie" value="None"/>
    <input id="w-1b5" name="timestamp" type="hidden" value="1473130831">
    <input id="w-1b6" name="spinner" type="hidden" value="XKXhx9SQY3wAOU1CbFDlKnFL0P-A">
    <p class="XNSArUxglNfCmPsVXYfrRGWeaQ">
    <label for="XLhAem0Fh7zAwHGgMo7oOw5tuHAU">You seem to have CSS turned off.
        Please don't fill out this field.</label><br>
    <input id="XLhAem0Fh7zAwHGgMo7oOw5tuHAU" name="XLxAem0Fh7z5Ba8csl30VVcjX2oI" type="text"><br></p>
    <p class="XNSArUxglNfCmPsVXYfrRGWeaQ">
    <label for="XLhAem0Fh7zEwHGgMo7oOw5tuHAU">You seem to have CSS turned off.
        Please don't fill out this field.</label><br>
    <input id="XLhAem0Fh7zEwHGgMo7oOw5tuHAU" name="XLxAem0Fh7j5Ba8csl30VVcjX2oI" type="text"><br></p>
</form>

    <a id="btn-float-close">No, thanks</a>
</div>


<div id="messages">
    
</div>


    <!-- ew:body_js -->


    <script type="text/javascript" src="https://a.fsdn.com/allura/nf/1472496229/_ew_/_slim/js?href=allura%2Fjs%2Fjquery.notify.js%3Ballura%2Fjs%2Fjquery.tooltipster.js%3Ballura%2Fjs%2Fsylvester.js%3Ballura%2Fjs%2Ftwemoji.min.js%3Ballura%2Fjs%2Fpb.transformie.min.js%3Ballura%2Fjs%2Fallura-base.js%3Ballura%2Fjs%2Fadmin_modal.js%3Bjs%2Fjquery.lightbox_me.js%3Btheme%2Fsftheme%2Fjs%2Fsftheme%2Fshared.js%3Ballura%2Fjs%2Fmaximize-content.js"></script>

    
<!-- /ew:body_js -->



    <!-- ew:body_js_tail -->


    
<!-- /ew:body_js_tail -->




<script type="text/javascript">(function() {
  $('#access_urls .btn').click(function(evt){
    evt.preventDefault();
    var parent = $(this).parents('.btn-bar');
    $(parent).find('input').val($(this).attr('data-url'));
    $(parent).find('span').text($(this).attr('title')+' access');
    $(this).parent().children('.btn').removeClass('active');
    $(this).addClass('active');
  });
  $('#access_urls .btn').first().click();

  
  var repo_status = document.getElementById('repo_status');
  // The repo_status div will only be present if repo.status != 'ready'
  if (repo_status) {
    $('.spinner').show()
    var delay = 500;
    function check_status() {
        $.get('/p/ramonelinux/code.git/status', function(data) {
            if (data.status === 'ready') {
                $('.spinner').hide()
                $('#repo_status h2').html('Repo status: ready. <a href=".">Click here to refresh this page.</a>');
            }
            else {
                $('#repo_status h2 span').html(data.status);
                if (delay < 60000){
                    delay = delay * 2;
                }
                window.setTimeout(check_status, delay);
            }
        });
    }
    var status_checker = window.setTimeout(check_status, delay);
    
  }
}());
</script>

<script type="text/javascript">(function() {
  $(window).bind('hashchange', function(e) {
    var hash = window.location.hash.substring(1);
	if ('originalEvent' in e && 'oldURL' in e.originalEvent) {
      $('#' + e.originalEvent.oldURL.split('#')[1]).css('background-color', 'transparent');
	}
    if (hash !== '' && hash.substring(0, 1) === 'l' && !isNaN(hash.substring(1))) {
      $('#' + hash).css('background-color', '#ffff99');
    }
  }).trigger('hashchange');

  var clicks = 0;
  $('.code_block').each(function(index, element) {
    $(element).bind('click', function() {
      // Trick to ignore double and triple clicks
      clicks++;
      if (clicks == 1) {
        setTimeout(function() {
          if (clicks == 1) {
            var hash = window.location.hash.substring(1);
            if (hash !== '' && hash.substring(0, 1) === 'l' && !isNaN(hash.substring(1))) {
              $('#' + hash).css('background-color', 'transparent');
            }
            $(element).css('background-color', '#ffff99');
            window.location.href = '#' + $(element).attr('id');
          };
          clicks = 0;
        }, 500);
      };
    });
  });
}());
</script>


    


    
        <script type="text/javascript" src='//consent-st.truste.com/get?name=notice.js&domain=slashdot.org&c=teconsent&text=true'></script>
    
    

<script>
    $(document).ready(function () {
        $(".tooltip").tooltipster({
            animation: 'fade',
            delay: 200,
            theme: 'tooltipster-light',
            trigger: 'hover',
            position: 'right',
            iconCloning: false,
            maxWidth: 300
        }).focus(function () {
            $(this).tooltipster('show');
        }).blur(function () {
            $(this).tooltipster('hide');
        });
    });
</script>
</body>
</html>