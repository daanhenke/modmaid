using System.Xml.Serialization;

namespace ModMaid.DoxyParser.Models.Xml;

[Serializable]
public class DoxySectionDefinition
{
  [XmlAttribute("kind")]
  public required string SectionKind { get; set; }

  [XmlElement("memberdef")]
  public required List<DoxyMemberDefinition> MemberDefinitions { get; set; }
}
