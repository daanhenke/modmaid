using System.Xml.Serialization;

namespace ModMaid.DoxyParser.Models.Xml;

public class DoxyLocation
{
  [XmlAttribute("file")] public required string File { get; set; }
  [XmlAttribute("line")] public required string Line { get; set; }
  [XmlAttribute("column")] public required int  Column { get; set; }

  [XmlAttribute("declfile")] public required string DeclarationFile { get; set; }
  [XmlAttribute("declline")] public required string DeclarationLine { get; set; }
  [XmlAttribute("declcolumn")] public required int  DeclarationColumn { get; set; }

  [XmlAttribute("bodyfile")] public required string BodyFile { get; set; }
  [XmlAttribute("bodyline")] public required string BodyLine { get; set; }
  [XmlAttribute("bodycolumn")] public required int  BodyColumn { get; set; }
}
