[![Travis CI](http://badges.herokuapp.com/travis/uncrustify/uncrustify?style=flat-square&env=BADGE=linux&label=Linux&branch=master)](https://travis-ci.org/uncrustify/uncrustify)
[![Travis CI](http://badges.herokuapp.com/travis/uncrustify/uncrustify?style=flat-square&env=BADGE=osx&label=OSX&branch=master)](https://travis-ci.org/uncrustify/uncrustify)
[![AppVeyor](https://img.shields.io/appveyor/ci/uncrustify/uncrustify/master.svg?style=flat-square&label=Windows)](https://ci.appveyor.com/project/uncrustify/uncrustify)
[![Coverity](https://scan.coverity.com/projects/8264/badge.svg)](https://scan.coverity.com/projects/uncrustify)
[![Coverage Status](https://coveralls.io/repos/github/uncrustify/uncrustify/badge.svg?branch=master)](https://coveralls.io/github/uncrustify/uncrustify?branch=master)
<a href="#"><img src="https://img.shields.io/badge/C++-11-blue.svg?style=flat-square"></a>

---------------------------

# Uncrustify
A source code beautifier for C, C++, C#, ObjectiveC, D, Java, Pawn and VALA

## Tianocore Fork Notes (Uncrustify Customizations for EDK II Source Code)

* Upstream Github repository: https://github.com/uncrustify/uncrustify

### Skip to Using EDK II Fork Steps 🏃

If you are just interested in the steps necessary to run the EDK II fork of Uncrustify against your code, visit the
[Tianocore Code Formatting wiki page](https://github.com/tianocore/tianocore.github.io/wiki/EDK-II-Code-Formatting).

### EDK II Details

This fork explores the use of Uncrustify for edk2 source code. The goal being to establish a configuration
for the tool that closely adheres to the
[EDK II C Coding Standards Specification](https://edk2-docs.gitbook.io/edk-ii-c-coding-standards-specification/). By
doing so, the tool can be used by developers to help reduce some of the tedious work involved in understanding and
applying the rules in the specification to their code. For general background on rationale behind the current set
of style guidelines and arguments for uniformity of style across the codebase, refer to the coding standards
specification.

The results from this tool should be considered a "best effort". Part of the work in the fork involves identifying
shortcomings and areas of ambiguity and deciding upon the best course of action. For example, Uncrustify
is highly customizable (as of version 0.72.0, 742 configuration options exist), eventually a scenario will have an
explicit rule defined in the Uncrustify configuration that was not explicitly defined in the coding standards
specification. A consensus must be reached about how to treat that particular scenario. In turn, the specification
might be updated to reflect this change. In other cases, a rule in the specification might not be enforceable in
Uncrustify as-is. Several options exist:

1. Ignore the rule in Uncrustify
2. Update the EDK II C Coding Standards Specification
3. Submit an upstream change to Uncrustify
4. Maintain an edk2 fork of Uncrustify with the change

Essential changes required in the Uncrustify tool led to this fork of Uncrustify for edk2.

Ideally, the changes could be upstreamed and the fork eliminated. The goal of this fork is to provide a dedicated area
for adapting Uncrustify to best support edk2 source code not to maintain a long term deviation from the mainline.

### Background

This work began by researching open source beautifiers capable of checking and formatting C/C++ source code
based on a set of rules in a configuration file. Three final options were considered:

1. [clang-format](https://clang.llvm.org/docs/ClangFormat.html) -
   [Not enough customization](https://clang.llvm.org/docs/ClangFormatStyleOptions.html). The tool has active
   development but the configuration file options available at the time were severely lacking what is needed
   to come close to the EDK II C Coding Standards Specification.
2. [Vera++](https://bitbucket.org/verateam/vera/wiki/Home) -
   [Not enough customization](https://bitbucket.org/verateam/vera/wiki/Rules). Development of the tool was not
   very active and the limited set of customization options made this a non-starter.
3. [Uncrustify](https://github.com/uncrustify/uncrustify) - The tool has active development and detailed customization
   options.

### Repository Branching Strategy

This repository maintains the following branches:

1. `master` - This is a direct copy of the upstream Uncrustify `master` branch. It is updated
   periodically to pull in upstream changes. This branch should be considered the "upstream" fork main.
   > ℹ️ _Note:_ The `master` branch is not used for any edk2-specific changes. It is only used to track upstream
     changes and provide a reference point for the `edk2/master` branch.
2. `edk2/master` - Contains edk2-specific changes on top of the `master` branch. This should be considered the "edk2"
   fork master.

The `master` branch is updated when a bug fix or feature needs to be pulled into the fork (there is not a set frequency).

To reduce maintenance overhead, these are currently the only two branches. If a strong need arises to base the edk2 changes
on Uncrustify releases, release branches will be made with the format `edk2/{uncrustify_release_tag}`. For example, the
Uncrustify 0.73.0 release would be maintained in the branch `edk2/0_73_0`.

### Current State

A configuration file is present in the edk2 branch(es) of Uncrustify [(`etc/edk2.cfg`)](https://github.com/tianocore/uncrustify/blob/edk2/master/etc/edk2.cfg)
that has been tweaked to get close to edk2 style. We request you return any changes that improve the file to better
adhere to the EDK II C Coding Standard so we can keep it up-to-date as the primary reference configuration file for
the project.

Due to a new configuration file option introduced `indent_func_call_edk2_style`, this branch will not work as-is with
the mainline version of Uncrustify.

While there's a few minor issues, some noteworthy deficiencies are below.

#### Missing: Naming Convention Check

See [3.1 Naming](https://edk2-docs.gitbook.io/edk-ii-c-coding-standards-specification/3_quick_reference#3-1-naming).

Many of the naming conventions can be likely be checked with a different tool. The most common violations include:

* Unclear variable names
* Not defining non-standard abbreviations/acronyms in the header file
* Not using Pascal case
* Capitalizing acronyms (e.g. MyPCIAddress)
* Not separating distinct words with an underscore in macro names (e.g. EACH_WORD_ISNOT_SEPARATE)
* Usage of Hungarian notation
* Global variables not prefixed with (g) and module variables not prefixed with (m)

The following issues in the main version of Uncrustify are what led to the fork. **They are resolved in the fork** but
information concerning the issues are kept here for reference.

### Key Issues Addressed in the Uncrustify Fork

#### Function Call Format

See [5.2.2.4](https://edk2-docs.gitbook.io/edk-ii-c-coding-standards-specification/5_source_files/52_spacing#5-2-2-4-subsequent-lines-of-multi-line-function-calls-should-line-up-two-spaces-from-the-beginning-of-the-function-name).

Uncrustify feature request:
[Feature Request: Multi-line function call argument indentation from function name · Issue #3077](https://github.com/uncrustify/uncrustify/issues/3077)

* The problem is that Uncrustify cannot indent function call arguments relative to the start of a function name.
* Uncrustify can indent function call arguments relative to the block indentation level or the open parenthesis level
  and/or align multi-line arguments to the first argument.
* Uncrustify can keep the first argument on the same line as the opening parenthesis or move it to the next line for
  a multi-line argument list.

#### Special Handling for DEBUG ()

Due to the way arguments to the `DEBUG ()` macro are substituted internally, the actual argument list is surrounded by
a pair of two opening and closing parenthesis.

This is uniquely different than the convention for other function / function macros which would normally put the
parenthesis on the next line to form a new indentation level.

* Uncrustify cannot make an exception for the `DEBUG ()` macro as-is.

---

## Features
* Highly configurable - 753 configurable options as of version 0.73.0
- <details><summary>add/remove spaces</summary>

  - `sp_before_sparen`: _Add or remove space before '(' of 'if', 'for', 'switch', 'while', etc._
  - `sp_compare`: _Add or remove space around compare operator '<', '>', '==', etc_
</details>

- <details><summary>add/remove newlines</summary>

  - `nl_if_brace`: _Add or remove newline between 'if' and '{'_
  - `nl_brace_while`: _Add or remove newline between '}' and 'while' of 'do' statement_
</details>

- <details><summary>add/remove blanklines</summary>

  - `eat_blanks_before_close_brace`: _Whether to remove blank lines before '}'_
  - `nl_max`: _The maximum consecutive newlines (3 = 2 blank lines)_
</details>

- <details><summary>indent code</summary>

  - `indent_switch_case`: _indent_switch_case: Spaces to indent 'case' from 'switch'_
  - `indent_class_colon`: _Whether to indent the stuff after a leading base class colon_
</details>

- <details><summary>align code</summary>

  - `align_func_params`: _Align variable definitions in prototypes and functions_
  - `align_struct_init_span`: _The span for aligning struct initializer values (0=don't align)_
</details>

- <details><summary>modify code</summary>

  - `mod_full_brace_for`: _Add or remove braces on single-line 'for' statement_
  - `mod_paren_on_return`: _Add or remove unnecessary paren on 'return' statement_
</details>

Here is an example [configuration file](https://raw.githubusercontent.com/uncrustify/uncrustify/master/documentation/htdocs/ben.cfg.txt),
and here is a [before](https://raw.githubusercontent.com/uncrustify/uncrustify/master/documentation/htdocs/examples/c-1.in.c)
and [after](https://raw.githubusercontent.com/uncrustify/uncrustify/master/documentation/htdocs/examples/c-1.out.c)
C source example.
That should give you a pretty good idea of what Uncrustify can do.





---------------------------------------------------------------------------

## Binaries
Pre compiled binaries for Windows can be downloaded [here](https://sourceforge.net/projects/uncrustify/files/uncrustify/).

## Build
[Python](https://www.python.org/) is an "interpreted high-level programming language for general-purpose programming", for this project it is needed to extend the capabilities of CMake.

[CMake](https://cmake.org/) is a tool that generates build systems
(Makefiles, Visual Studio project files, Xcode project files and others).

To generate a build system for Uncrustify using CMake, create a build
folder and run CMake from it:

```bash
$ mkdir build
$ cd build
$ cmake ..
```
(Use `cmake -G Xcode ..` for Xcode)

Then use the build tools of your build system (in many cases this will
simply be `make`, but on Windows it could be MSBuild or Visual Studio).
Or use CMake to invoke it:

```bash
$ cmake --build .
```

If testing is enabled, CMake generates a `test` target, which you can
_build_ using your build system tools (usually `make test`). This can also
be invoked using CTest:

```bash
$ ctest -V -C Debug
```

There is also an `install` target, which can be used to install the
Uncrustify executable (typically `make install`).

### A note on CMake configurations
Some build systems are single-configuration, which means you specify the
build type when running CMake (by setting the `CMAKE_BUILD_TYPE`
variable), and the generated files then build that configuration.

An example of a single-configuration build system are Makefiles. You can
build the Release configuration of Uncrustify (from the build folder) with:

```bash
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ make
```

Other build systems are multi-configuration, which means you specify the
build type when building.

An example of a multi-configuration build system are Visual Studios project
files. When you open the project in Visual Studio, you can select which
configuration to build. You can also do this while building from the
command line with `cmake --build . --config Release`.


## Bugs
Post any bugs to the issue tracker found on the projects GitHub page:
  https://github.com/uncrustify/uncrustify/issues

Please include the following with your issue:
 - a description of what is not working right
 - input code sufficient to demonstrate the issue
 - expected output code
 - configuration options used to generate the output

More about this is in the [ISSUE_TEMPLATE](https://github.com/uncrustify/uncrustify/blob/master/.github/ISSUE_TEMPLATE)


### Known problems
[Look at the Wiki](https://github.com/uncrustify/uncrustify/wiki/Known-Problems)


## Which repositories have uncrustify?
[Look here](https://repology.org/metapackage/uncrustify/versions)


## Contribute
If you want to add a feature, fix a bug, or implement missing
functionality, feel free to do so! Patches are welcome!
Here are some areas that need attention:

- __Patches for Objective-C support__. We really need someone who knows
  this language as it has more than plenty open issues. A good starting
  point would be to integrate changes made in the
  [Unity fork](https://github.com/Unity-Technologies/uncrustify/tree/fixes/c-oc-java)
- Test Java support and provide feedback (or patches!)
- Test Embedded SQL to see what works
- A logo of some sort
- Anything else that you want to do to make it better?

### A note about pull requests
Firstly take a look at the [CONTRIBUTING.md](https://github.com/uncrustify/uncrustify/blob/master/CONTRIBUTING.md)

Currently we have two continuous integration systems that test your PRs,
TravisCI and Appveyor.
Tested are the test cases, the formatting of the code base and
the output of the command line options.

Test cases can be found in the `tests/` directory. Every file ending with
`.test` is a test set. Inside each line with these components is a
single test: `testNr[!] testConfigFileName testInputFileName [lang]`

The configuration file `testConfigFileName` has to be located inside `tests/config`,
the input file `testInputFileName` inside `tests/input/<testSetName>/`,
and expected results file inside the `tests/expected/<testSetName>/`
directory.
Expected results have the following naming convention: `testNr-testInputFileName`.

Optionally a `!` can follow the `testNr` to enable a custom rerun
configuration.
Rerun configurations need to be named like this:
`testConfigFileName`(without extension)+`.rerun`+`.extension`

Also, optionally a language for the input can be provided with `lang`.

The codebase has to be formatted by the options set up in
`forUncrustifySources.cfg`. Failing to format the sources correctly will
cause TravisCI build failures.

The Command line interface (CLI) output is tested by the
`test_cli_options.sh` script. It is located inside of `tests/cli/` and operates
on the subdirectories of that folder.

If a PR is altering the CLI output, files inside those directories might
need to be manually updated. This often happens when options are
added, removed or altered. Keep in mind that the version string line
(example: `# Uncrustify-0.69.0_f`) of outputs from commands like
`--show-config` should be replaced with a blank line.

### Debugging

The first method is to use uncrustify itself to get debug informations.
Using:
```.txt
   uncrustify -c myExample.cfg -f myExample.cpp -p myExample.p -L A 2>myExample.A
```
you get two files for the first informations.
The p-file gives you details of the parsing process and indentation.
```.txt
# Line                Tag              Parent          Columns Br/Lvl/pp     Flag   Nl  Text
#   1>              CLASS[               NONE][  1/  1/  6/  0][0/0/0][  10070000][0-0] class
#   1>               TYPE[              CLASS][  7/  7/ 14/  1][0/0/0][  10000000][0-0]       Capteur
#   1>         BRACE_OPEN[              CLASS][ 15/ 15/ 16/  1][0/0/0][ 100000400][0-0]               {
```

The A-file gives you many details about the run itself, where the process is running thru,
which values have the most important variables.
```.txt
tokenize(2351): orig_line is 1, orig_col is 1, text() 'class', type is CLASS, orig_col_end is 6
tokenize(2351): orig_line is 1, orig_col is 7, text() 'Capteur', type is WORD, orig_col_end is 14
tokenize(2351): orig_line is 1, orig_col is 15, text() '{', type is BRACE_OPEN, orig_col_end is 16
```

It might be usefull to add some code lines to see where something is happening.
Use the package `unc_tools`.
Remove the comment at line:
```.cpp
#define DEVELOP_ONLY
```
Import the package:
```.cpp
#include "unc_tools.h"
```
Add at some places the line:
```.cpp
prot_the_line(__LINE__, 6, 0);
```
Compile again with DEBUG option.



### How to add an option

If you need a new option, there are a few steps to follow.
Take as example the option `sp_trailing_ret_t`

First define the option:
- Insert the code below to the file src/options.h
_NOTE:
This file is processed by make_options.py, and must conform to a particular
format. Option groups are marked by '//begin ' (in upper case; this example
is lower case to prevent being considered a region marker for code folding)
followed by the group description. Options consist of two lines of
declaration preceded by one or more lines of C++ comments. The comments form
the option description and are taken verbatim, aside from stripping the
leading '// '. Only comments immediately preceding an option declaration,
with no blank lines, are taken as part of the description, so a blank line
may be used to separate notations from a description.
An option declaration is 'extern TYPE\nNAME;', optionally followed by
' // = VALUE' if the option has a default value that is different from the
default-constructed value type of the option. The 'VALUE' must be valid C++
code, and is taken verbatim as an argument when creating the option's
instantiation. Note also that the line break, as shown, is required.
_
```.cpp
// Add or remove space around trailing return operator '->'.
extern Option<iarf_e>
sp_trailing_ret_t;
```
- Insert the code below to the file src/space.cpp
```.cpp
   if (chunk_is_token(first, CT_TRAILING_RET_T))
   {
      // Add or remove space around trailing return operator '->'.
      log_rule("sp_trailing_ret_t");
      return(options::sp_trailing_ret_t());
   }
```


### Portability

We are pretty sure that nothing OS-specific is used in the code base.
The software has been previously tested on the following operating systems:
- Linux
- QNX
- OS X
- FreeBSD, NetBSD, OpenBSD
- Sun Solaris 9
- Windows (binary available)


---------------------------------------------------------------------------

## Running the program

__NOTE__ This application works reasonably well but it has bugs. Do __not__
apply it on your whole codebase without checking the results!

Here are ways to run it:
```
$ uncrustify -c mystyle.cfg -f somefile.c -o somefile.c.unc
$ uncrustify -c mystyle.cfg -f somefile.c > somefile.c.unc
$ uncrustify -c mystyle.cfg somefile.c
$ uncrustify -c mystyle.cfg --no-backup somefile.c
$ uncrustify -c mystyle.cfg *.c
$ uncrustify -c mystyle.cfg --no-backup *.c
```
The `-c` flag selects the configuration file.
The `-f` flag specifies the input file.
The `-o` flag specifies the output file.
If flag `-f` is used without flag `-o` the output will be send to `stdout`.

Alternatively multiple or single files that should be processed can be
specified at the command end without flags.
If the flag `--no-backup` is missing, every file is saved with the initial
name and an additional suffix (can be changed with --suffix).

For more options descriptions call:
```bash
$ uncrustify -h
```

## Configuring the program
Uncrustify usually reads configuration files that are passed via the `-c`
flag. If the flag is not provided Uncrustify will try to find a
configuration file via the `UNCRUSTIFY_CONFIG` environment variable or a
file with the name `.uncrustify.cfg` or `uncrustify.cfg` in your home folder.

To get a list of:
- all available options use:
  ```bash
  uncrustify --show-config
  ```

- all available options in a usable configuration file format use:
  ```bash
  uncrustify --update-config
  ```

  or

  ```bash
  uncrustify --update-config-with-doc
  ```

  As the names suggest both options can produce output that adds newly
  introduced options to your old configuration file. For this your old
  configuration file has to be passed via the `-c` flag:
  ```bash
  uncrustify --update-config-with-doc -c path/to/your.cfg
  ```

Example configuration files that can be used as a starting point can be
found in the `etc/` directory (such as [ben.cfg](./etc/ben.cfg)).

Modify to your liking. Use a quality side-by-side diff tool to determine
if the program did what you wanted. Repeat until your style is refined.

To ease the process a bit, some 3rd party tools are available:
- [Universal Indent GUI](http://universalindent.sourceforge.net/) - A
  cross-platform graphical configuration file editor for many code
  beautifiers, including Uncrustify.
- [uncrustify_config](https://github.com/CDanU/uncrustify_config) - A web
  configuration tool based on Uncrustify's emscripten interface.
- [UncrustifyX](https://github.com/ryanmaxwell/UncrustifyX) - Uncrustify
  utility and documentation browser for Mac OS X

Under Windows:
Uncrustify is a command-line tool, if you run it by double-clicking the
executable, it will open a command prompt run the executable
(which prints the help message), and then immediately close the window
as uncrustify exits.

You can open the command prompt (which is an interactive terminal
window that allows you to run commands without it closing as soon as
they exit) and run uncrustify.exe there.

## Using uncrustify with vim
Have a look [here]https://github.com/cofyc/vim-uncrustify
