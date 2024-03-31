using System.Xml.Serialization;

namespace ModMaid.DoxyParser.Models.Xml;

[Serializable]
public class DoxyCompoundDefinition
{
  [XmlAttribute("id")] public required string Id { get; set; }
  [XmlAttribute("kind")] public required DoxyMemberKind Kind { get; set; }
  [XmlElement("compoundname")] public required string Name { get; set; }
  [XmlElement("innerclass")] public required List<DoxyInnerClass> InnerClasses { get; set; }
  [XmlElement("sectiondef")] public required List<DoxySectionDefinition> SectionDefinitions { get; set; }
}
