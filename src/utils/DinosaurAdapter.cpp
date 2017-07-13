// --------------------------------------------------------------------------
//                   OpenMS -- Open-Source Mass Spectrometry
// --------------------------------------------------------------------------
// Copyright The OpenMS Team -- Eberhard Karls University Tuebingen,
// ETH Zurich, and Freie Universitaet Berlin 2002-2017.
//
// This software is released under a three-clause BSD license:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of any author or any participating institution
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
// For a full list of authors, refer to the file AUTHORS.
// --------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL ANY OF THE AUTHORS OR THE CONTRIBUTING
// INSTITUTIONS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// --------------------------------------------------------------------------
// $Maintainer: Chris Bielow $
// $Authors: Clemens Groepl, Chris Bielow$
// --------------------------------------------------------------------------

#include <OpenMS/FORMAT/FeatureXMLFile.h>
#include <OpenMS/KERNEL/FeatureMap.h>

#include <OpenMS/APPLICATIONS/TOPPBase.h>
#include <OpenMS/MATH/STATISTICS/LinearRegression.h>

#include <OpenMS/SYSTEM/File.h>

#include <map>
#include <vector>
#include <algorithm>

using namespace OpenMS;
using namespace Math;
using namespace std;

typedef Feature::CoordinateType CoordinateType;

//-------------------------------------------------------------
//Doxygen docu
//-------------------------------------------------------------

/**
    @page TOPP_AdditiveSeries AdditiveSeries

    @brief Computes an additive series to quantify a peptide in a set of samples.
<CENTER>
    <table>
        <tr>
            <td ALIGN = "center" BGCOLOR="#EBEBEB"> pot. predecessor tools </td>
            <td VALIGN="middle" ROWSPAN=3> \f$ \longrightarrow \f$ AdditiveSeries \f$ \longrightarrow \f$</td>
            <td ALIGN = "center" BGCOLOR="#EBEBEB"> pot. successor tools </td>
        </tr>
        <tr>
      <td VALIGN="middle" ALIGN = "center" ROWSPAN=1> @ref TOPP_FeatureFinderCentroided </td>
            <td VALIGN="middle" ALIGN = "center" ROWSPAN=2> - </td>
        </tr>
        <tr>
            <td VALIGN="middle" ALIGN = "center" ROWSPAN=1> @ref TOPP_IDMapper </td>
        </tr>
    </table>
</CENTER>
    This module computes an additive series for an absolute
    quantification of a peptide in a set of samples. The
    output consists of a GNUplot script which can be used
    to visualize the results and some XML output for further processing.

    In this version, the application computes the additive
    series as a ratio of the intensities of two different peptides.
    One of these peptides serves as internal standard for
    calibration.

    <B>The command line parameters of this tool are:</B>
    @verbinclude TOPP_AdditiveSeries.cli
    <B>INI file documentation of this tool:</B>
    @htmlinclude TOPP_AdditiveSeries.html
*/

// We do not want this class to show up in the docu:
/// @cond TOPPCLASSES

class DinosaurAdapter :
  public TOPPBase
{
public:
    DinosaurAdapter() :
    TOPPBase("DinosaurAdapter",
             "Analyzes mzML data using the feature detector Dinosaur.",
             false)
  {
  }

protected:
  void registerOptionsAndFlags_()
  {
    registerInputFileList_("in", "<files>", StringList(), "input files separated by blanks", true);
    setValidFormats_("in", ListUtils::create<String>("mzML"));
    registerOutputFile_("out", "<file>", "", "output tsv file containg detected features");
    setValidFormats_("out", ListUtils::create<String>("tsv"));
  }

  ExitCodes main_(int, const char **)
  {

    writeLog_("Hello world to log!");

    return EXECUTION_OK;
  }

};

int main(int argc, const char ** argv)
{
  DinosaurAdapter tool;
  return tool.main(argc, argv);
}

/// @endcond
