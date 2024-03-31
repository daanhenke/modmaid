<script setup lang="ts">
  const route = useRoute();
  const {data: namespace} = await useAsyncData('namespace', () => queryContent(`/docs/namespaces/${route.params.slug}`).findOne());
  console.log(namespace, route.params.slug);
</script>

<template>
  <h2>Namespace {{ namespace.name }}</h2>

  <div v-if="namespace.aliases.length > 0">
    <h3>Aliases</h3>
    <div v-for="alias in namespace.aliases">
      <h4>{{ alias.name }} = {{ alias.baseType }};</h4>
    </div>
  </div>

  <div v-if="namespace.globals.length > 0">
    <h3>Global Variables</h3>
    <div v-for="global in namespace.globals">
      <h4>{{ global.name }}</h4>
    </div>
  </div>

  <div v-if="namespace.classes.length > 0">
    <h3>Classes</h3>
    <div v-for="clazz in namespace.classes">
      <h4>{{ clazz.name }}</h4>
    </div>
  </div>

  <div v-if="namespace.functions.length > 0">
    <h3>Functions</h3>
    <div v-for="func in namespace.functions">
      <h4>{{ func.name }}();</h4>
    </div>
  </div>
</template>

<style scoped>

</style>
