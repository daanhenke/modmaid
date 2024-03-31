using System.Xml.Serialization;

namespace ModMaid.DoxyParser.Models.Xml;

[Serializable, XmlRoot("doxygen")]
public class DoxyRoot
{
  [XmlElement("compounddef")]
  public required DoxyCompoundDefinition CompoundDefinition { get; set; }
}
