using System.Xml.Serialization;

namespace ModMaid.DoxyParser.Models.Xml;

[Serializable]
public class DoxyMemberDefinition
{
  [XmlAttribute("kind")] public DoxyMemberKind Kind { get; set; }
  [XmlAttribute("id")] public required string Id { get; set; }
  [XmlAttribute("prot")] public required DoxyProtectionLevel ProtectionLevel { get; set; }

  [XmlAttribute("static")] public required DoxyBool IsStatic { get; set; }
  [XmlAttribute("const")] public required DoxyBool IsConst { get; set; }
  [XmlAttribute("explicit")] public required DoxyBool IsExplicit { get; set; }
  [XmlAttribute("inline")] public required DoxyBool IsInline { get; set; }

  [XmlElement("type")] public required DoxyType Type { get; set; }
  [XmlElement("name")] public required string Name { get; set; }
  [XmlElement("qualifiedname")] public required string FullName { get; set; }
  [XmlElement("location")] public required DoxyLocation Location { get; set; }
}
