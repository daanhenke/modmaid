using System.Xml.Serialization;

namespace ModMaid.DoxyParser.Models.Xml;

[Serializable]
public class DoxyCompound
{
  [XmlAttribute("refid")]
  public required string ReferenceId { get; set; }

  [XmlAttribute("kind")]
  public DoxyMemberKind Kind { get; set; }

  [XmlElement("name")]
  public required string Name { get; set; }
}
