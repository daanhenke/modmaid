using AutoMapper;
using ModMaid.DoxyParser.Models.Xml;
using ModMaid.DoxyParser.Models.Yaml;

namespace ModMaid.DoxyParser;

public class TypeMapper
{
  private readonly IMapper _mapper;

  public TypeMapper()
  {
    _mapper = new MapperConfiguration(Configure)
      .CreateMapper();
  }

  public YamlNamespace ConvertNamespace(DoxyCompoundDefinition root)
    => _mapper.Map<YamlNamespace>(root);

  private static void Configure(IMapperConfigurationExpression cfg)
  {
    cfg.CreateMap<DoxyCompoundDefinition, YamlNamespace>()
      .ForMember(m => m.Classes, m => m.MapFrom(m => m.InnerClasses))
      .ForMember(m => m.Aliases, m => m.MapFrom(m => m
        .SectionDefinitions
        .Where(m => m.SectionKind == "typedef")
        .SelectMany(m => m.MemberDefinitions))
      )
      .ForMember(m => m.Globals, m => m.MapFrom(m => m
        .SectionDefinitions
        .Where(m => m.SectionKind == "var")
        .SelectMany(m => m.MemberDefinitions))
      )
      .ForMember(m => m.Functions, m => m.MapFrom(m => m
        .SectionDefinitions
        .Where(m => m.SectionKind == "func")
        .SelectMany(m => m.MemberDefinitions))
      );

    cfg.CreateMap<DoxyInnerClass, YamlClassReference>()
      .ForMember(m => m.Id, m => m.MapFrom(m => m.ReferenceId))
      .ForMember(m => m.Name, m => m.MapFrom(m => m.FullName));

    cfg.CreateMap<DoxyMemberDefinition, YamlAlias>()
      .ForMember(m => m.BaseType, m => m.MapFrom(m => m.Type.Name));
    cfg.CreateMap<DoxyMemberDefinition, YamlGlobal>()
      .ForMember(m => m.Type, m => m.MapFrom(m => m.Type.Name));
    cfg.CreateMap<DoxyMemberDefinition, YamlFunction>()
      .ForMember(m => m.ReturnType, m => m.MapFrom(m => m.Type.Name));
  }
}
