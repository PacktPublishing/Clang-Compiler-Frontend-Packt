// ClassComplexityDiag.td
// Diagnostic Groups.
class DiagGroup<string Name, list<DiagGroup> subgroups = []> {
  string GroupName = Name;
  list<DiagGroup> SubGroups = subgroups;
  string CategoryName = "";
  code Documentation = [{}];
}
class InGroup<DiagGroup G> { DiagGroup Group = G; }

// Textual substitutions which may be performed on the text of diagnostics
class TextSubstitution<string Text> {
  string Substitution = Text;
  // TODO: These are only here to allow substitutions to be declared inline with
  // diagnostics
  string Component = "";
  string CategoryName = "";
  bit Deferrable = 0;
}


// Define the diagnostic severities.
class Severity<string N> {
  string Name = N;
}
def SEV_Ignored : Severity<"Ignored">;
def SEV_Remark  : Severity<"Remark">;
def SEV_Warning : Severity<"Warning">;
def SEV_Error   : Severity<"Error">;
def SEV_Fatal   : Severity<"Fatal">;

class DefaultWarn   { Severity DefaultSeverity = SEV_Warning; }

// Define the diagnostic classes.
class DiagClass;
def CLASS_NOTE      : DiagClass;
def CLASS_REMARK    : DiagClass;
def CLASS_WARNING   : DiagClass;
def CLASS_EXTENSION : DiagClass;
def CLASS_ERROR     : DiagClass;

class SFINAEResponse;
def SFINAE_SubstitutionFailure : SFINAEResponse;
def SFINAE_Suppress            : SFINAEResponse;
def SFINAE_Report              : SFINAEResponse;
def SFINAE_AccessControl       : SFINAEResponse;

// All diagnostics emitted by the compiler are an indirect subclass of this.
class Diagnostic<string summary, DiagClass DC, Severity defaultmapping> {
  /// Component is specified by the file with a big let directive.
  string         Component = ?;
  string         Summary = summary;
  DiagClass      Class = DC;
  SFINAEResponse SFINAE = SFINAE_Suppress;
  bit            AccessControl = 0;
  bit            WarningNoWerror = 0;
  bit            ShowInSystemHeader = 0;
  bit            ShowInSystemMacro = 1;
  bit            Deferrable = 0;
  Severity       DefaultSeverity = defaultmapping;
  DiagGroup      Group;
  string         CategoryName = "";
}


class Warning<string str>   : Diagnostic<str, CLASS_WARNING, SEV_Warning>;

def ClassComplexity : DiagGroup<"class-complexity">;

def warn_class_too_complex : Warning<"class %0 is too complex: method count = %1">,
  InGroup<ClassComplexity>, DefaultWarn;
