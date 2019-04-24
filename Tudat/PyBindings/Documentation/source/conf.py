# -*- coding: utf-8 -*-
#
# Configuration file for the Sphinx documentation builder.
#
# This file does only contain a selection of the most common options. For a
# full list see the documentation:
# http://www.sphinx-doc.org/en/master/config

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
# import os
# import sys
# sys.path.insert(0, os.path.abspath('.'))

import os
import sys
sys.path.insert(0,"../../../bin")
sys.path.insert(0,"../../../../bin")


import sys, os, re, glob, collections

def isBoostFunc(what,obj):
    return what=='function' and obj.__repr__().startswith('<Boost.Python.function object at 0x')

def isBoostMethod(what,obj):
    "I don't know how to distinguish boost and non-boost methods..."
    return what=='method' and obj.__repr__().startswith('<unbound method ');

def replaceLaTeX(s):
    # replace single non-escaped dollars $...$ by :math:`...`
    # then \$ by single $
    s=re.sub(r'(?<!\\)\$([^\$]+)(?<!\\)\$',r'\ :math:`\1`\ ',s)
    return re.sub(r'\\\$',r'$',s)

def fixSrc(app,docname,source):
    source[0]=replaceLaTeX(source[0])

def fixDocstring(app,what,name,obj,options,lines):
    for i in range(0,len(lines)): lines[i]=lines[i]
    # remove empty default roles, which is not properly interpreted by docutils parser
    for i in range(0,len(lines)):
        lines[i]=lines[i].replace(':ydefault:``','')
        lines[i]=lines[i].replace(':yattrtype:``','')
        lines[i]=lines[i].replace(':yattrflags:``','')
        #lines[i]=re.sub(':``',':` `',lines[i])
    # remove signature of boost::python function docstring, which is the first line of the docstring
    if isBoostFunc(what,obj):
        l2=boostFuncSignature(name,obj)[1]
        # we must replace lines one by one (in-place) :-|
        # knowing that l2 is always shorter than lines (l2 is docstring with the signature stripped off)
        for i in range(0,len(lines)):
            lines[i]=l2[i] if i<len(l2) else ''
    elif isBoostMethod(what,obj):
        l2=boostFuncSignature(name,obj)[1]
        if (l2):
            for i in range(0,len(lines)):
                lines[i]=l2[i] if i<len(l2) else ''
    # LaTeX: replace $...$ by :math:`...`
    # must be done after calling boostFuncSignature which uses original docstring
    for i in range(0,len(lines)): lines[i]=replaceLaTeX(lines[i])


def boostFuncSignature(name,obj,removeSelf=False):
    """Scan docstring of obj, returning tuple of properly formatted boost python signature
    (first line of the docstring) and the rest of docstring (as list of lines).
    The rest of docstring is stripped of 4 leading spaces which are automatically
    added by boost.
    
    removeSelf will attempt to remove the first argument from the signature.
    """
    doc=obj.__doc__
    if doc==None: # not a boost method
        return None,None
    nname=name.split('.')[-1]
    docc=doc.split('\n')
    if len(docc)<2: return None,docc
    doc1=docc[1]
    # functions with weird docstring, likely not documented by boost
    if not re.match('^'+nname+r'(.*)->.*$',doc1):
        return None,docc
    if doc1.endswith(':'): doc1=doc1[:-1]
    strippedDoc=doc.split('\n')[2:]
    # check if all lines are padded
    allLinesHave4LeadingSpaces=True
    for l in strippedDoc:
        if l.startswith('    '): continue
        allLinesHave4LeadingSpaces=False; break
    # remove the padding if so
    if allLinesHave4LeadingSpaces: strippedDoc=[l[4:] for l in strippedDoc]
    for i in range(len(strippedDoc)):
        # fix signatures inside docstring (one function with multiple signatures)
        strippedDoc[i],n=re.subn(r'([a-zA-Z_][a-zA-Z0-9_]*\() \(object\)arg1(, |)',r'\1',strippedDoc[i].replace('->','→'))
    # inspect dosctring after mangling
    if 'getViscoelasticFromSpheresInteraction' in name and False:
        print name
        print strippedDoc
        print '======================'
        for l in strippedDoc: print l
        print '======================'
    sig=doc1.split('(',1)[1]
    if removeSelf:
        # remove up to the first comma; if no comma present, then the method takes no arguments
        # if [ precedes the comma, add it to the result (ugly!)
        try:
            ss=sig.split(',',1)
            if ss[0].endswith('['): sig='['+ss[1]
            else: sig=ss[1]
        except IndexError:
            # grab the return value
            try:
                sig=') -> '+sig.split('->')[-1]
        #if 'Serializable' in name: print 1000*'#',name
            except IndexError:
                sig=')'
    return '('+sig,strippedDoc

def fixSignature(app, what, name, obj, options, signature, return_annotation):
    #print what,name,obj,signature#,dir(obj)
    if what=='attribute':
        doc=unicode(obj.__doc__)
        ret=''
        m=re.match('.*:ydefault:`(.*?)`.*',doc)
        if m:
            typ=''
            #try:
            #    clss='.'.join(name.split('.')[:-1])
            #    instance=eval(clss+'()')
            #    typ='; '+getattr(instance,name.split('.')[-1]).__class__.__name__
            #    if typ=='; NoneType': typ=''
            #except TypeError: ##no registered converted
            #    typ=''
            dfl=m.group(1)
            m2=re.match(r'\s*\(\s*\(\s*void\s*\)\s*\"(.*)\"\s*,\s*(.*)\s*\)\s*',dfl)
            if m2: dfl="%s, %s"%(m2.group(2),m2.group(1))
            if dfl!='': ret+=' (='+dfl+'%s)'%typ
            else: ret+=' (=uninitalized%s)'%typ
        #m=re.match('.*\[(.{,8})\].*',doc)
        #m=re.match('.*:yunit:`(.?*)`.*',doc)
        #if m:
        #    units=m.group(1)
        #    print '@@@@@@@@@@@@@@@@@@@@@',name,units
        #    ret+=' ['+units+']'
        return ret,None
    elif what=='class':
        ret=[]
        if len(obj.__bases__)>0:
            base=obj.__bases__[0]
            while base.__module__!='Boost.Python':
                ret+=[base.__name__]
                if len(base.__bases__)>0: base=base.__bases__[0]
                else: break
        if len(ret):
            return ' (inherits '+u' → '.join(ret)+')',None
        else: return None,None
    elif isBoostFunc(what,obj):
        sig=boostFuncSignature(name,obj)[0] or ' (wrapped c++ function)'
        return sig,None
    elif isBoostMethod(what,obj):
        sig=boostFuncSignature(name,obj,removeSelf=True)[0]
        return sig,None
    #else: print what,name,obj.__repr__()
    #return None,None


def setup(app):
    pass
    app.connect('autodoc-process-docstring',fixDocstring)
    app.connect('autodoc-process-signature',fixSignature)



# -- Project information -----------------------------------------------------

project = 'PyTudat'
copyright = '2019, TU Delft'
author = 'TU Delft'

# The short X.Y version
version = ''
# The full version, including alpha/beta/rc tags
release = ''


# -- General configuration ---------------------------------------------------

# If your documentation needs a minimal Sphinx version, state it here.
#
# needs_sphinx = '1.0'

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.doctest',
    'sphinx.ext.todo',
    'sphinx.ext.coverage',
    'sphinx.ext.mathjax',
    'sphinx.ext.ifconfig',
    'sphinx.ext.viewcode',
    'sphinx.ext.githubpages',
]

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# The suffix(es) of source filenames.
# You can specify multiple suffix as a list of string:
#
# source_suffix = ['.rst', '.md']
source_suffix = '.rst'

# The master toctree document.
master_doc = 'index'

# The language for content autogenerated by Sphinx. Refer to documentation
# for a list of supported languages.
#
# This is also used if you do content translation via gettext catalogs.
# Usually you set "language" from the command line for these cases.
language = None

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path .
exclude_patterns = []

# The name of the Pygments (syntax highlighting) style to use.
pygments_style = 'sphinx'


# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'alabaster'

# Theme options are theme-specific and customize the look and feel of a theme
# further.  For a list of options available for each theme, see the
# documentation.
#
# html_theme_options = {}

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']

# Custom sidebar templates, must be a dictionary that maps document names
# to template names.
#
# The default sidebars (for documents that don't match any pattern) are
# defined by theme itself.  Builtin themes are using these templates by
# default: ``['localtoc.html', 'relations.html', 'sourcelink.html',
# 'searchbox.html']``.
#
# html_sidebars = {}


# -- Options for HTMLHelp output ---------------------------------------------

# Output file base name for HTML help builder.
htmlhelp_basename = 'PyTudatdoc'


# -- Options for LaTeX output ------------------------------------------------

latex_elements = {
    # The paper size ('letterpaper' or 'a4paper').
    #
    # 'papersize': 'letterpaper',

    # The font size ('10pt', '11pt' or '12pt').
    #
    # 'pointsize': '10pt',

    # Additional stuff for the LaTeX preamble.
    #
    # 'preamble': '',

    # Latex figure (float) alignment
    #
    # 'figure_align': 'htbp',
}

# Grouping the document tree into LaTeX files. List of tuples
# (source start file, target name, title,
#  author, documentclass [howto, manual, or own class]).
latex_documents = [
    (master_doc, 'PyTudat.tex', 'PyTudat Documentation',
     'TU Delft', 'manual'),
]


# -- Options for manual page output ------------------------------------------

# One entry per manual page. List of tuples
# (source start file, name, description, authors, manual section).
man_pages = [
    (master_doc, 'pytudat', 'PyTudat Documentation',
     [author], 1)
]


# -- Options for Texinfo output ----------------------------------------------

# Grouping the document tree into Texinfo files. List of tuples
# (source start file, target name, title, author,
#  dir menu entry, description, category)
texinfo_documents = [
    (master_doc, 'PyTudat', 'PyTudat Documentation',
     author, 'PyTudat', 'One line description of project.',
     'Miscellaneous'),
]


# -- Extension configuration -------------------------------------------------

# -- Options for todo extension ----------------------------------------------

# If true, `todo` and `todoList` produce output, else they produce nothing.
todo_include_todos = True
