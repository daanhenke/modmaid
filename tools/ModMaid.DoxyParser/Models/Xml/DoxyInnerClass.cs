using System.Xml.Serialization;

namespace ModMaid.DoxyParser.Models.Xml;

[Serializable]
public class DoxyInnerClass
{
  [XmlAttribute("refid")]
  public required string ReferenceId { get; set; }

  [XmlAttribute("prot")]
  public DoxyProtectionLevel ProtectionLevel { get; set; }

  [XmlText]
  public required string FullName { get; set; }
}
