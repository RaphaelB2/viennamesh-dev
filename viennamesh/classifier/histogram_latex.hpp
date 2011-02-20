/* =============================================================================
   Copyright (c) 2011, Institute for Microelectronics, TU Wien
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMesh - The Vienna Mesh Generation Framework
                             -----------------

   authors:    Josef Weinbub                         weinbub@iue.tuwien.ac.at
               Franz Stimpfl
               Rene Heinzl


   license:    see file LICENSE in the base directory
============================================================================= */

#ifndef VIENNAMESH_CLASSIFIER_HISTOGRAMLATEX_HPP
#define VIENNAMESH_CLASSIFIER_HISTOGRAMLATEX_HPP

#include <iomanip>

namespace viennamesh {

   

   
   
// -------------------------------------------------------------------------------------------------
template < int DIM >
struct writeLatex { };

template < >
struct writeLatex <2> 
{
   typedef std::map<std::string, int> histogram_type;
   
   static void eval(histogram_type p, std::ostream& ostr = std::cout)
   {
     ostr << std::fixed << std::setprecision(8);

     int sum = 0;
     histogram_type::iterator it;

     for(it = p.begin(); it != p.end(); it++)
       {
         sum += it->second;
       }

     // ##########
     // create statistics plot
     ostr << std::endl;
     ostr << "%-----------" << std::endl;
     ostr << "%%% PLOT %%%" << std::endl;
     ostr << "%-----------" << std::endl;
     ostr << "\\begin{minipage}[ht]{0.20\\textwidth}" << std::endl;
     ostr << "\\setlength{\\unitlength}{1cm}" << std::endl;
     ostr << "\\psset{xunit=0.7cm, yunit=0.03017058cm}" << std::endl;
     ostr << "\\begin{pspicture}(-1.0,-40.0)(8,130)" << std::endl;
     ostr << "\\psaxes[labels=y,Dx=1,Dy=50.](0,0)(3,100)" << std::endl;
     ostr << "\\pspolygon[fillcolor=black, fillstyle=solid](-0.08,104.55414013)(0,109.53290870)(0.08,104.55414013)" << std::endl;
     
     int i=0;
     for(it = p.begin(); it != p.end(); it++)
       {
         double percentage = ( boost::lexical_cast<double>(it->second) /  boost::lexical_cast<double>(sum))*100.0;
         
         ostr.precision(2);
         ostr << "\\psframe[linewidth=1pt, fillcolor=gray, fillstyle=solid] (" << i << ".30000000,0)(" << i << ".70000000," << percentage << ")" << std::endl;
         ostr << "\\rput[bl](" << i++ << ".35000000,-35){\\rotateleft{\\footnotesize " << it->first << "}}" << std::endl;
       }
     
     ostr << "\\end{pspicture}" << std::endl;
     ostr << "\\end{minipage}" << std::endl;

     ostr << std::endl;

     ostr << "%------------" << std::endl;
     ostr << "%%% TABLE %%%" << std::endl;
     ostr << "%------------" << std::endl;
     
     // ##########
     // create statistics table
     ostr << "\\begin{minipage}[ht]{0.20\\textwidth}" << std::endl;
     ostr << "\\begin{tabular}{crr}" << std::endl;
     
     for(it = p.begin(); it != p.end(); it++)
       {
         double percentage = ( boost::lexical_cast<double>(it->second) /  boost::lexical_cast<double>(sum))*100.0;

         ostr << it->first << " & " << it->second << " & " << percentage << "\\% \\\\" << std::endl;
       }

     ostr << "\\end{tabular}" << std::endl;
     ostr << "\\end{minipage}" << std::endl;
     ostr << "%------------" << std::endl;
     ostr << "%------------" << std::endl;
     ostr << std::endl;   
   }
};

template < >
struct writeLatex <3> 
{
   typedef std::map<std::string, int> histogram_type;
   
   static void eval(histogram_type p, std::ostream& ostr = std::cout)
   {
     int sum = 0;
     histogram_type::iterator it;

     for(it = p.begin(); it != p.end(); it++)
       {
         sum += it->second;
       }

     // ##########
     // create statistics plot
     ostr << "%-----------" << std::endl;
     ostr << "%%% PLOT %%%" << std::endl;
     ostr << "%-----------" << std::endl;
     ostr << "\\begin{minipage}[ht]{0.40\\textwidth}" << std::endl;
     ostr << "\\setlength{\\unitlength}{1cm}" << std::endl;
     ostr << "\\psset{xunit=0.7cm, yunit=0.03017058cm}" << std::endl;
     ostr << "\\begin{pspicture}(-1.0,-40.0)(8,130)" << std::endl;
     ostr << "\\psaxes[labels=y,Dx=1,Dy=50.](0,0)(8,100)" << std::endl;
     ostr << "\\pspolygon[fillcolor=black, fillstyle=solid](-0.08,104.55414013)(0,109.53290870)(0.08,104.55414013)" << std::endl;
     
     int i=0;
     for(it = p.begin(); it != p.end(); it++)
       {
         double percentage = ( boost::lexical_cast<double>(it->second) /  boost::lexical_cast<double>(sum))*100.0;
         
         ostr.precision(2);
         ostr << "\\psframe[linewidth=1pt, fillcolor=gray, fillstyle=solid] (" << i << ".30000000,0)(" << i << ".70000000," << percentage << ")" << std::endl;
         ostr << "\\rput[bl](" << i++ << ".35000000,-35){\\rotateleft{\\footnotesize " << it->first << "}}" << std::endl;
       }
     
     ostr << "\\end{pspicture}" << std::endl;
     ostr << "\\end{minipage}" << std::endl;

     ostr << std::endl;

     ostr << "%------------" << std::endl;
     ostr << "%%% TABLE %%%" << std::endl;
     ostr << "%------------" << std::endl;
     
     // ##########
     // create statistics table
     ostr << "\\begin{minipage}[ht]{0.20\\textwidth}" << std::endl;
     ostr << "\\begin{tabular}{crr}" << std::endl;
     
     for(it = p.begin(); it != p.end(); it++)
       {
         double percentage = ( boost::lexical_cast<double>(it->second) /  boost::lexical_cast<double>(sum))*100.0;

         ostr << it->first << " & " << it->second/4 << " & " << percentage << "\\% \\\\" << std::endl;
       }

     ostr << "\\end{tabular}" << std::endl;
     ostr << "\\end{minipage}" << std::endl;
     ostr << "%------------" << std::endl;
     ostr << "%------------" << std::endl;   
   }
};   
   
} // end namespace viennamesh

# endif