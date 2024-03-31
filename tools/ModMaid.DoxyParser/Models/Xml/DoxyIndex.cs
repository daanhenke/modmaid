using System.Xml.Serialization;

namespace ModMaid.DoxyParser.Models.Xml;

[Serializable, XmlRoot("doxygenindex")]
public class DoxyIndex
{
  [XmlElement("compound")]
  public required List<DoxyCompound> Children { get; set; }
}
