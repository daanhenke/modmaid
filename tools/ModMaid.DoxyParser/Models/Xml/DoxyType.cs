using System.Xml.Serialization;

namespace ModMaid.DoxyParser.Models.Xml;

[Serializable]
public class DoxyType
{
  [XmlText] public string? Name { get; set; }
  [XmlElement("ref")] public string? Reference { get; set; }
}
